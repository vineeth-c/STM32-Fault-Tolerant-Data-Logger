# Concurrency Model

Single-core cooperative foreground execution plus interrupt producers. ISR/foreground shared queues are bounded. Buffer ownership remains with the submitter until completion unless a module explicitly copies data. No firmware dynamic allocation is used. Critical sections must protect compound shared-state changes when hardware implementations are added.
