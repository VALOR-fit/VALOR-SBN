# VALOR SBN

The VALOR-SBN repository includes SBN-specific codes and configurations for the **VALOR SBN oscillation analysis and workflow**. It is built on top of the common *Software Development Kit* (VALOR-SDK repository), which includes the bulk of the VALOR analysis code which is experiment agnostic.

This README, includes key summary information on the evolution and variants of the VALOR SBN oscillation analysis, including information on which VALOR-SBN and VALOR-SDK branches, as well as which data products, are required for reproducing publicly-shown results. This README also lists the naming conventions used for labelling VALOR SBN analyses, analysis configurations and related data products.

** Contents **
- List of VALOR branches and data products used for the main public results
- Labelling of VALOR analysis variants and of sets of data products
- Information on SBN MC productions used in VALOR
- Information on VALOR/SBN systematic error parameterizations


## List of VALOR branches and data products used for the main public results

A number of SBN analysis variants can be supported in the code included in each VALOR-SBN branch. Although each VALOR-SBN branch may work with several different VALOR-SDK branches, the actual SDK branch that was used in the context of each analysis is also listed below, to provide a combination of products which are guaranteed to work and to allow the replication of analysis results.

| SBN branch  | SDK branch  | Supported SBN analysis variants  | 
|-------------|-------------|----------------------------------|
|             |             |                                  |
|             |             |                                  |


## Labelling of VALOR analysis variants and of sets of data products

For each **set of data products** required for running an analysis, VALOR uses the following naming scheme: 
<pre>
       [sbn analysis type]_[sbn mc production]_[systematic error parameterization]
 (eg.:    sbn_numu_disapp              2019a1                                02a1)
</pre>
where the conventions used for enumerating a) MC productions and b) VALOR/SBN systematic error parameterizations will be summarised at a later section.

These labels can be used for downloading all relevant data products (belonging to that set) using the '%**valor_data-fetch-set** --data-set=*label* ...' command.

For more information on the VALOR data distribution scripts, see 
https://github.com/VALOR-fit/VALOR-SDK/tree/master/scripts/data_distribution

A list of VALOR SBN data products can be found in:
https://github.com/VALOR-fit/VALOR-SDK/blob/master/scripts/data_distribution/config/data_products/SBN.dat


Several **analysis variants** can be built using the same set of data products.
These analysis variants are labelled as:
<pre>
       [set of data products]_[revision]
 (eg.:             see above          1)
</pre>
These analysis variant labels are used for labelling the analysis configuration XML files made available in the VALOR-SBN repository.

| Analysis variant               | Comments    |
|--------------------------------|-------------|
| sbn_numu_disapp_2019a1_01a1_1  | 2019a1 proposal-era GENIE-2.12 MC; 01a1 systematics |
| sbn_numu_disapp_2019b1_01a1_1  | 2019b1 'modern' GENIE-2.12 MC; 01a1 systematics |
| sbn_numu_disapp_2019b2_01a1_1  | 2019b2 'modern' GENIE-2.12 MC; 01a1 systematics |
| sbn_numu_disapp_2019b2_02a1_1  | 2019b2 'modern' GENIE-2.12 MC; 02a1 systematics |
| sbn_numu_disapp_2019b2_02a2_1  | 2019b2 'modern' GENIE-2.12 MC; 02a2 systematics |


## Information on SBN MC productions used in VALOR

VALOR uses the following naming scheme for **SBN MC productions**: 
<pre>
           [date][physics model][revision]
     (eg.:  2020              a         1)
</pre>
A summary of all SBN MC productions used is given in the table below.

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

## Information on VALOR/SBN systematic error parameterizations

VALOR uses the following naming scheme for its **SBN systematic error parameterizations**. A number of different *generations* of error parameterizations can exist, each with several versions, each of which can have numerous minor revisons:
<pre>
      [generation][version][revision]
(eg.:          01        a         1)
</pre>

A summary of all error parameterizations implemented in the VALOR SBN analysis is given below.

| Err param | Detector | Flux  | Interaction  | Comments  |
|-----------|----------|-------|--------------|-----------|
| 01a1 | n/a  | COV_1(loc,flav,Ereco) | COV_1(Ereco) | Last version of the 01 parameterization still at use while establishing this table on 04/2020; Used for the 01/2020 Fermilab PAC studies and the associated SBN-OSC WG tech note |
| 02a1 | n/a  | COV_1(loc,flav,Etrue) | COV_1(Ereco) | **Temporary:** Stopgap implementation towards the full 02 parameterization; used at the 03/2020 SBN analysis workshop |
| 02a2 | COV_0(det,sample,mode,Ereco) (**DET: 2020a1**) | as in 02a1 | as in 02a1 | **Temporary:** Adding first version of detector systematics on 02a1 |

| 02b1 | n/a  | COV(loc,flav,Etrue) (**FLUX: REF?**) | RESP_1 + ad hoc 50% MEC systematic (**XSEC: REF?**) | |
| 02b2 | COV(det,sample,mode,Ereco) (**DET: 2020a1**) | as in 02b1 | as in 02b1 | |
| 02c1 | n/a  | hadroproduction: COV(loc,flav,Etrue); optics: RESP_1 (**FLUX: REF?**) | as in 02b1 | |
| 02c2 | COV(det,sample,mode,Ereco) (**DET: 2020a1**) | as in 02c1 | as in 02b1 | |

Methods:
 - **COV_0 {'space'}**: Normalisation parameters acting on a set of bin in the specified 'space', with an error matrix filled in by hand.
 - **COV_1 {'space'}**: Normalisation parameters acting on a set of bin in the specified 'space', with a corresponding error matrix computed from underlying model parameter throws included in MC production.
 - **RESP_1**: Non-linear 1D response functions computed from underlying model parameter throws included in MC production, operating on MC templates bins.

(DET: 2020a1) https://www.overleaf.com/read/nmxtrndczyks

## Information on mock data analysed with VALOR / SBN

(Perhaps this more detailed info could be stored somewhere else?)

The following are revision qualifiers of the mock_data data products.

| Err param | Comments  |
|-----------|-----------|
| 09a2019   | Mock data for the muon-neutrino disappearance analysis, produced for the 09/2019 analysis workshop (MD.1) |
| 03a2020   | Mock data for the muon-neutrino disappearance analysis, produced for the 03/2020 analysis workshop (MD.1) |

(MD.1) 
Datasets 1-5 using GENIE 3.0.6; Datasets 11-15 using GENIE 2.12.10;
Datasets i and 10+i have an identical systematic variation, but on a different underlying cross-section model.

*Dataset 1*: 

- unchanged flux
- unchanged interaction model for given GENIE tune
- unchanged detector response
- no oscillations

*Dataset 2*:

- unchanged flux
- Decrease CCQE by 10% for Q^2 < 0.3 GeV^2 and decrease by 3% in remaining Q^2 range.
- Increase CCMEC by 50%.
- Throw away a random 20% of CC1\pi events where the \pi is subsequently absorbed (emulate \Delta + N -> N + N)
- Increase NC bkg by 30%
- unchanged detector response
- no oscillations

*Dataset 3*: 

- not revealed yet

*Dataset 4*: 

- not revealed yet

*Dataset 5*: 

- not revealed yet

