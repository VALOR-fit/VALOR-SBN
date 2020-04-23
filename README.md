# VALOR SBN

This repository includes SBN-spefic codes and configurations for the VALOR SBN oscillation analysis.

Naming scheme applicable to both the 'dsts' and 'universes' minor qualifiers

sbn mc productions: [date][physics model][revision]
              (eg.:  2020              a         1)

-----------|---------|-----------|----------------|--------------------------|--------------------------------------------------------------------------------------------
| MC prod  | Flux    | GENIE vrs | GENIE tune     | SBNCode                  | Comments
-----------|---------|-----------|----------------|--------------------------|--------------------------------------------------------------------------------------------
| 2019a1   | configF | v2.12.10  | Default+MEC    | v2.2                     | `proposal'; last respin of 2019a still in use while establishing this archive on 04/2020
| 2019b1   | configF | v2.12.10  | Default+MEC    | v2.2                     | `modern';   last respin of 2019b still in use while establishing this archive on 04/2020
| 2019b2   | configF | v2.12.10  | Default+MEC    | v2.2, gputnam-workshop   | `modern';   batch of files made available after the 09/2019 SBN analysis workshop
| 2020a1   | configF | v3.0.6    | G18_10a_02_11a | gputnam-workshop0320-gen | `modern';   batch of files made available after the 03/2020 SBN analysis workshop
-----------|---------|-----------|----------------|--------------------------|--------------------------------------------------------------------------------------------

[1] https://cdcvs.fnal.gov/redmine/projects/sbncode/wiki/Fitter_Validation_NuMu_sample: SBNCode v2.2, 'modern' and 'proposal'
[2] https://cdcvs.fnal.gov/redmine/projects/sbn-analysis-group/wiki/How_to_access_Workshop_Osc_samples: SBNCode workshop-game samples, modern only from here on
