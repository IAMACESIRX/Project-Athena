# Open Questions

## Project Management

- Should the game client use partial tracking first, such as `WTF`, `Interface`, ReShade config, and realmlist files?
- Should live-state snapshots be dated folders instead of overwriting a single `Server-Live-State` folder?
- Should local bare repos be mirrored to another local drive later?

## Server Operations

- Is the active server currently running from this backup copy or from another original project path?
- Should LAN realm address be set during restore automatically?
- Should restore scripts prompt for database password instead of hardcoding the default?

## AI Automation

- What actions should AI be allowed to run automatically against the live server?
- Which actions require explicit human confirmation?
- Should AI maintain a generated inventory of SQL tables and game-client account files?
