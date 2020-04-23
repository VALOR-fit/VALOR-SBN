# VALOR SBN

This repository includes SBN-spefic codes and configurations for the VALOR SBN oscillation analysis.

This README, includes information on the evolution of the VALOR SBN oscillation analysis, 
including information on which VALOR-SBN and VALOR-SDK branches, as well as which data products, 
are required for reproducing publicly-shown results. 
This README also lists the naming conventions used for labelling VALOR SBN analyses, 
analysis configurations and data products.

## List of VALOR branches and data products used for the main public results

| SBN branch  | SDK branch  | Data product sets  | Comments
|-------------|-------------|--------------------|-------------|
|             |             |                    |
|             |             |                    |


## Labelling of analysis variants and of sets of data products

For each **set of data products** VALOR uses the following naming scheme: 
<pre>
       [sbn analysis type]_[sbn mc production]_[systematic error parameterization]
 (eg.:    sbn_numu_disapp              2019a1                                02a1)
</pre>

Several **analysis variants** can be built using the same set of data products.
These analysis variants are labelled as:
<pre>
       [set of data products]_[revision]
 (eg.:             see above          1)
</pre>


## SBN MC productions

VALOR uses the following naming scheme for SBN MC productions: 
** \[date (eg 2010)\] \[physics model / configuration (eg a)\] \[revision (eg 1)\]**

| MC prod  | Flux    | GENIE vrs | GENIE tune     | SBNCode                  | Comments
|----------|---------|-----------|----------------|--------------------------|--------------------------------------------------------------------------------------------
| 2019a1   | configF | v2.12.10  | Default+MEC    | v2.2                     | `proposal'; last respin of 2019a still in use while establishing this archive on 04/2020
| 2019b1   | configF | v2.12.10  | Default+MEC    | v2.2                     | `modern';   last respin of 2019b still in use while establishing this archive on 04/2020
| 2019b2   | configF | v2.12.10  | Default+MEC    | v2.2, gputnam-workshop   | `modern';   batch of files made available after the 09/2019 SBN analysis workshop
| 2020a1   | configF | v3.0.6    | G18_10a_02_11a | gputnam-workshop0320-gen | `modern';   batch of files made available after the 03/2020 SBN analysis workshop

- [1] https://cdcvs.fnal.gov/redmine/projects/sbncode/wiki/Fitter_Validation_NuMu_sample: 
SBNCode v2.2, 'modern' and 'proposal'
- [2] https://cdcvs.fnal.gov/redmine/projects/sbn-analysis-group/wiki/How_to_access_Workshop_Osc_samples: 
SBNCode workshop-game samples, modern only from here on

