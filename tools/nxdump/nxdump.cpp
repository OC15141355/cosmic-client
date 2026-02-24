#include <iostream>
#include <string>

// NoLifeNx headers from cosmic-client
#include <nlnx/nx.hpp>
#include <nlnx/node.hpp>
#include <nlnx/file.hpp>
#include <nlnx/bitmap.hpp>

void dump_node(nl::node n, const std::string& prefix, int depth, int max_depth) {
    if (depth > max_depth) return;
    for (auto child : n) {
        std::string indent(depth * 2, ' ');
        std::cout << indent << child.name();
        switch (child.data_type()) {
            case nl::node::type::string:
                std::cout << " = \"" << child.get_string() << "\"";
                break;
            case nl::node::type::integer:
                std::cout << " = " << child.get_integer();
                break;
            case nl::node::type::real:
                std::cout << " = " << child.get_real();
                break;
            case nl::node::type::vector: {
                auto v = child.get_vector();
                std::cout << " [vector] = (" << v.first << ", " << v.second << ")";
                break;
            }
            case nl::node::type::bitmap: {
                nl::bitmap bmp = child.get_bitmap();
                std::cout << " [bitmap " << bmp.width() << "x" << bmp.height() << "]";
                break;
            }
            case nl::node::type::audio:
                std::cout << " [audio]";
                break;
            default:
                break;
        }
        std::cout << std::endl;
        dump_node(child, prefix + "/" + std::string(child.name()), depth + 1, max_depth);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: nxdump <file.nx> <path> [depth]" << std::endl;
        std::cerr << "  path: slash-separated path like Back/login.img" << std::endl;
        std::cerr << "  depth: max depth to dump (default 2)" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string path = argv[2];
    int max_depth = argc > 3 ? std::stoi(argv[3]) : 2;

    try {
        nl::nx::load_all();
    } catch (...) {
        // load_all needs Base.nx, so load individual file
    }

    // Load individual file
    nl::file f(filename);
    nl::node root = f;

    // Navigate to the specified path (slash-separated to preserve dots in node names like "Login.img")
    nl::node current = root;
    if (path != ".") {
        size_t start = 0;
        while (start < path.size()) {
            size_t sep = path.find('/', start);
            if (sep == std::string::npos) sep = path.size();
            std::string part = path.substr(start, sep - start);
            if (!part.empty()) {
                current = current[part.c_str()];
            }
            start = sep + 1;
        }
    }

    std::cout << "Dumping: " << filename << " / " << path << " (depth=" << max_depth << ")" << std::endl;
    std::cout << "---" << std::endl;
    dump_node(current, path, 0, max_depth);

    return 0;
}
