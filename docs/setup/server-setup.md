# Server Setup

TwinleafStory uses a fork of [Cosmic](https://github.com/P0nk/Cosmic), a MapleStory v83 server emulator written in Java.

## Quick Start (Docker)

The server is deployed on 192.168.0.25 via Docker:

```bash
cd server
docker-compose up -d
```

This starts the server on port 8484 (login) and channels on 7575-7577.

## Manual Setup

### Prerequisites

- Java 17+
- MySQL 8.0+

### Database

```bash
# Create database and import schema
mysql -u root -p < server/database/cosmic.sql
```

### Configuration

Edit `server/config.yaml`:
- `server.host`: Server IP address
- `server.port`: Login port (default: 8484)
- `database.host`: MySQL host
- `database.user` / `database.password`: DB credentials

### Build and Run

```bash
cd server
./mvnw clean package
java -jar target/cosmic-*.jar
```

## Client Configuration

The client connects to the server address in `build/Settings`:

```
ServerIP = 192.168.0.25
ServerPort = 8484
```

## Key Server Files

| File | Purpose |
|------|---------|
| `config.yaml` | Server configuration |
| `src/main/java/constants/net/SendOpcode.java` | Server→client opcodes |
| `src/main/java/constants/net/RecvOpcode.java` | Client→server opcodes |
| `tools/PacketCreator.java` | Packet construction |
| `net/server/coordinator/session/Hwid.java` | HWID validation |
| `database/cosmic.sql` | Database schema |
