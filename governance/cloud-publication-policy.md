# Cloud Publication Policy

## Default rule

Project Athena is local-first. Publication is denied by default unless the human
operator explicitly authorizes a defined set of files or a pull request.

A public GitHub repository is a publication surface, not the authoritative live
runtime and not permission to upload the complete local Athena memory.

## Publication classes

| Class | Default | Examples |
|---|---|---|
| Public architecture | Explicitly authorized | Specifications, diagrams, public roadmaps |
| Public source | Explicitly authorized | Sanitized tools, schemas, test scaffolds |
| Public generated report | Review required | Reports that contain no private paths, secrets, personal data, or live-state detail |
| Private project memory | Prohibited | Personal context, private handoffs, unpublished research, local evidence |
| Runtime state | Prohibited | Credentials, tokens, databases, process state, private logs, device state |
| Third-party material | Licence review required | External code, images, datasets, model files, documents |

## Required controls

1. State the exact publication target: branch, pull request, issue, or mirror.
2. Minimize the publication set to the files required for the task.
3. Remove credentials, private paths, personal information, and unnecessary
   local-state details.
4. Label mirrors as mirrors; GitHub/local Project Athena remains canonical only
   after a reviewed merge.
5. Use a pull request for non-trivial publication.
6. Record skipped validation and unresolved licence questions.
7. Never interpret permission to publish one task as standing permission for
   future unrelated material.

## Compatibility rule

`project.cloud_push_allowed` remains `false` in the machine-readable manifest to
preserve the default-deny contract used by existing tools. The more precise
publication classes in this policy define the controlled exception process.
