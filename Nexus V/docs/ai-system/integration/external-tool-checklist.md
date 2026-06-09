# External Tool Checklist

Before connecting a new program or software tool, answer:

- What does it read?
- What does it write?
- Can it mutate live server/client state?
- Does it need network access?
- Does it use Git?
- Can it accidentally push to a cloud remote?
- Where does it log output?
- How do we disable or remove it?
- What evidence proves it worked?

## Registration

If accepted, add it to:

- `integration/adapter-registry.yml`
- `manifests/tool-index.yml`
- `manifests/capability-matrix.yml`
- relevant playbook or module card.
