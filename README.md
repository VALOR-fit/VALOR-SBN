# VALOR SBN

The VALOR-SBN repository includes SBN-specific codes and configurations for the **VALOR SBN oscillation analysis and workflow**. It is built on top of the common *Software Development Kit* (VALOR-SDK repository), which includes the bulk of the VALOR analysis code which is experiment agnostic.

This README, includes key summary information on the evolution and variants of the VALOR SBN oscillation analysis, including information on which VALOR-SBN and VALOR-SDK branches, as well as which data products, are required for reproducing publicly-shown results. This README also lists the naming conventions used for labelling VALOR SBN analyses, analysis configurations and related data products.

**Contents**
- [List of VALOR branches and data products used for the main public results]
- [Labelling of analysis variants and of sets of data products]


## List of VALOR branches and data products used for the main public results

A number of SBN analysis variants can be supported in the code included in each VALOR-SBN branch. Although each VALOR-SBN branch may work with several different VALOR-SDK branches, the actual SDK branch that was used in the context of each analysis is also listed below, to provide a combination of products which are guaranteed to work and to allow the replication of analysis results.

| SBN branch  | SDK branch  | Supported SBN analysis variants  | 
|-------------|-------------|----------------------------------|
|             |             |                                  |
|             |             |                                  |


## Labelling of analysis variants and of sets of data products

For each **set of data products** required for running an analysis, VALOR uses the following naming scheme: 
<pre>
       [sbn analysis type]_[sbn mc production]_[systematic error parameterization]
 (eg.:    sbn_numu_disapp              2019a1                                02a1)
</pre>
where the conventions used for enumerating MC productions and error parameterizations will be summarised at a later section.

These labels can be used for downloading all relevant data products using %**valor_data-fetch-set** --data-set=*label* ...

For more information on the VALOR data distribution scripts, see 
https://github.com/VALOR-fit/VALOR-SDK/tree/master/scripts/data_distribution


Several **analysis variants** can be built using the same set of data products.
These analysis variants are labelled as:
<pre>
       [set of data products]_[revision]
 (eg.:             see above          1)
</pre>
These analysis variant labels are used for labelling the analysis configuration XML files made available in the VALOR-SBN repository.

| Analysis variant               | Comments    |
|--------------------------------|-------------|
| sbn_numu_disapp_2019a1_01a1_1  | SBN proposal MC production using sbncode v2.2 and all systematics in Ereco binned normalisations |
| sbn_numu_disapp_2019b1_01a1_1  | SBN 'modern' MC production using sbncode v2.2 and all systematics in Ereco binned normalisations |
| sbn_numu_disapp_2019b2_01a1_1  | SBN 'modern' MC production using sbncode v2.2 on a feature branch produced for the Sept2019 analysis workshop, all syst in Ereco normalisations |
| sbn_numu_disapp_2019b2_02a1_1  | SBN 'modern' MC production using sbncode v2.2 on a feature branch produced for the Sept2019 analysis workshop, interaction in Ereco, flux in Etrue |


## Information on SBN MC productions 

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

| Err param | Detector | Flux                              | Interaction              | Comments
|-----------|----------|-----------------------------------|--------------------------|---------------|
| 01a1      | n/a      | Ereco bin norm /flavour /location | Ereco bin norm. / mode   | a1 is the last version/revision of the 01 parameterization still at use while establishing this table on 04/2020 |
| 02a1      | n/a      | Etrue bin norm /flavour /location | Ereco bin norm. / mode   | a1 is a stopgap implementation towards the full 02 parameterization; used at the 03/2020 SBN analysis workshop |
| 02b1      | n/a      | Etrue bin norm /flavour /location | Non-linear responses for all xsec systematics in input DSTs | b1 is the first complete implementation of the 02 parameterization |
