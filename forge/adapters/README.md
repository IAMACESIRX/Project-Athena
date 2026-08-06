# F.O.R.G.E. AIO Adapter

F.O.R.G.E. does not maintain independent pairwise contracts. It reads and writes the shared contract defined by `contracts/AIO-MASTER-CONTRACT.yml`.

F.O.R.G.E. owns the candidate-lattice, symmetric-challenge, mechanism-mining, reverse-reconstruction and simplification phases. Any F.O.R.G.E.–specific contract view must be generated from the current AIO instance with `tools/aio_contract.py view`; it is non-authoritative and must preserve the instance hash and lineage.
