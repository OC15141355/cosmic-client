# Phase 1: Dev Box Setup

Checklist for the new R5 3600 / GTX 1650 / 16GB Windows PC (Centrecom Nunawading, $450 AUD).

## Hardware

- CPU: Ryzen 5 3600
- GPU: GTX 1650
- RAM: 16 GB
- Storage: 500 GB NVMe

---

## Setup Checklist

### 1. OS Install

- [ ] Install Windows 10 or 11
- [ ] Run Windows Update to latest
- [ ] Install GPU drivers (GeForce Experience or driver-only from nvidia.com)

### 2. Network & SSH

- [ ] Connect to LAN (bridged, not NAT if using a VM host)
- [ ] Note the IP address: `192.168.0.___`
- [ ] Add Pi-hole DNS entry: `devbox.homelab → <IP>`
- [ ] Enable OpenSSH Server:
  ```powershell
  # PowerShell (Admin)
  Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
  Start-Service sshd
  Set-Service -Name sshd -StartupType Automatic
  ```
- [ ] Add firewall rule (should auto-create, verify):
  ```powershell
  New-NetFirewallRule -Name "OpenSSH-Server" -DisplayName "OpenSSH Server (sshd)" -Enabled True -Direction Inbound -Protocol TCP -Action Allow -LocalPort 22
  ```
- [ ] Test SSH from MacBook: `ssh <user>@<IP>`
- [ ] Add to `~/.ssh/config` on MacBook (with ProxyJump through core-01 if desired)

### 3. Copy Game Files

- [ ] SCP the MapleStory client from MacBook:
  ```bash
  # From MacBook
  scp -r ~/Games/MapleStoryCX/ <user>@<devbox-ip>:C:/Games/MapleStoryCX/
  ```
- [ ] Verify NX files are present: `Map.nx`, `Mob.nx`, `String.nx`, etc.
- [ ] Copy fonts directory if needed

### 4. Patch Client EXE

The client binary has the server IP hardcoded. Needs hex-editing to point to the Cosmic server.

- [ ] Identify current server IP in binary (likely `100.82.13.36` — Tailscale IP)
- [ ] Replace with `192.168.0.25` (LAN direct to MapleStory VM on hv-01)
- [ ] Alternative: keep Tailscale IP if testing remotely
- [ ] Tool: HxD (free hex editor for Windows) or `xxd` on Linux

### 5. Test Login (THE LITMUS TEST)

- [ ] Launch client EXE
- [ ] Login screen appears
- [ ] Enter credentials (auto-register is ON — any new user/pass creates an account)
- [ ] PIC screen works (this is where Wine/CrossOver fails)
- [ ] Select channel
- [ ] Character select / creation works
- [ ] Enter game world
- [ ] Walk around Henesys
- [ ] Chat works
- [ ] Open inventory, equipment, skills windows

**If PIC screen fails**: Check server logs at `192.168.0.25`, verify port 8484 is reachable, check client IP patch.

### 6. Install Dev Tools

- [ ] **Git**: https://git-scm.com/download/win (or `winget install Git.Git`)
- [ ] **Java 17+**: Eclipse Temurin or Oracle JDK (`winget install EclipseAdoptium.Temurin.17.JDK`)
- [ ] **Maven**: For building Cosmic server (`winget install Apache.Maven`)
- [ ] **MySQL client**: MySQL Workbench or DBeaver for `drop_data` table edits
- [ ] **VS Code**: For NPC scripts and WZ XML editing (`winget install Microsoft.VisualStudioCode`)
- [ ] **Python 3**: For any scripting needs (`winget install Python.Python.3.12`)
- [ ] **HaRepacker Resurrected v6.0**: WZ editor (see [WZ Pipeline](wz-pipeline.md))
  - Download from: https://github.com/lastbattle/Harepacker-resurrected/releases
  - v6.0 uses .NET Framework 4.8 (pre-installed on Win 10/11)
- [ ] **HxD**: Hex editor for client patching (https://mh-nexus.de/en/hxd/)

### 7. Clone Repo

```powershell
cd C:\Projects
git clone git@github.com:OC15141355/TwinleafStory.git
```

- [ ] Verify repo clones successfully
- [ ] Check `server/wz/` directory is populated
- [ ] Check `server/scripts/npc/` has 708 JS files

### 8. Set Up WZ Editing Workspace

- [ ] Unzip `wz.zip` (98 MB) to a working directory:
  ```
  C:\WZ-Workspace\
  ├── Mob.wz/
  ├── Map.wz/
  ├── Item.wz/
  ├── String.wz/
  └── ... (16 categories)
  ```
- [ ] Copy community repack IMGs if needed for HaRepacker
- [ ] Test opening a WZ file in HaRepacker (use "GMS (old)" encryption)

---

## Verification Checklist

| Test | Status |
|------|--------|
| SSH from MacBook to devbox | |
| Client launches | |
| Login screen appears | |
| PIC screen passes (!!) | |
| Enter channel | |
| Walk around in-game | |
| Git repo cloned | |
| HaRepacker opens WZ files | |
| MySQL client connects to docker-01 | |
| Java 17 installed and `mvn --version` works | |

---

## Network Diagram

```
MacBook (.92) ──── LAN ──── Dev Box (.???)
                    │
                    ├── core-01 (.105) ── SSH jumphost
                    ├── docker-01 (.21) ── MySQL (drop_data)
                    ├── MapleStory VM (.25) ── Cosmic server :8484
                    └── Pi-hole (.14) ── DNS
```

## Post-Setup

Once the dev box is verified working:
1. Move to [Boss Audit](boss-audit.md) — play the game, fill in findings
2. Start testing bosses with a GM character (use `!setgmlevel 6` in-game or set in DB)
