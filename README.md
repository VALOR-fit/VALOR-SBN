# VALOR SBN

The VALOR-SBN repository includes SBN-specific codes and configurations for the **VALOR SBN sterile neutrino oscillation fit and related analysis workflows**. It is built on top of the common and experiment-agnostic [VALOR *Software Development Kit (SDK)*](https://github.com/VALOR-fit/VALOR-SDK/) which includes the bulk of the VALOR analysis code.

**Copyright (c) 2010-2020**, The VALOR Fitting Group. All Rights Reserved.

**Authors (VALOR/SBN):** Costas Andreopoulos (*Liverpool & STFC/RAL*), Dom Barker (*Sheffield*), Steve Dennis (*Cambridge*), Thomas Ham (*Liverpool*), Rhiannon Jones (*Liverpool*), Glória de Sá Pereira (*Liverpool & STFC/RAL*)

For a full list of VALOR SDK authors, see [here](https://valor.pp.rl.ac.uk/).

## Code, analysis and input data product versioning scheme

This README, includes key summary information on the evolution and variants of the VALOR SBN oscillation analysis, including information on which VALOR-SBN and VALOR-SDK branches, as well as which data products, are required for reproducing publicly-shown results. This README also lists the naming conventions used for labelling VALOR SBN analyses, analysis configurations and related data products. More detailed information can be found in the [VALOR SBN wiki](https://github.com/VALOR-fit/VALOR-SBN/wiki).

**Contents**
- List of VALOR branches and data products used for the main public results
- Labelling of VALOR analysis variants and of sets of data products
- Information on SBN MC productions used in VALOR
- Information on VALOR/SBN systematic error parameterizations

### List of VALOR branches and data products used for the main public results

A number of SBN analysis variants can be supported in the code included in each VALOR-SBN branch. Although each VALOR-SBN branch may work with several different VALOR-SDK branches, the actual SDK branch that was used in the context of each analysis is also listed below, to provide a combination of products which are guaranteed to work and to allow the replication of analysis results.

| SBN branch  | SDK branch  | Supported SBN analysis variants  | 
|-------------|-------------|----------------------------------|
|             |             |                                  |
|             |             |                                  |


### Labelling of VALOR analysis variants and of sets of data products

For each **set of data products** required for running an analysis, VALOR uses the following naming scheme: 
<pre>
       [sbn analysis type]_[sbn mc production]_[systematic error parameterization]
 (eg.:    sbn_numu_disapp              2019a1                                02a1)
</pre>
where the conventions used for enumerating a) MC productions and b) VALOR/SBN systematic error parameterizations will be summarised at a later section.

These labels can be used for downloading all relevant data products (belonging to that set) using the '%**valor_data-fetch-set** --data-set=*label* ...' command.

For more information on the VALOR data distribution scripts, see 
https://github.com/VALOR-fit/VALOR-SDK/tree/master/config/data_distribution

A list of VALOR SBN data products can be found in:
https://github.com/VALOR-fit/VALOR-SDK/blob/master/config/data_distribution/products/sbn.dat


Several **analysis variants** can be built using the same set of data products.
These analysis variants are labelled as:
<pre>
       [set of data products]_[revision]
 (eg.:             see above          1)
</pre>
These names of analysis variants are used for labelling the main analysis configuration XML files made available in the VALOR-SBN repository. A list and a brief description of our main SBN analysis variants is given below. Analysis variants supported by the version of the code that includes this file as shown in bold.

| Analysis label. | Type   | Samples | Fit distributions | MC pro | Syst. | Comment |
|-----------------|--------|---------|-------------------|--------|-------|---------|
| **sbn_numu_disapp_2019a1_01a1_1** | Eff. 3+1 numu disap | numuCC-like (x3 det) | Enu_reco | 2019a1 | 01a1 | |
| **sbn_numu_disapp_2019b1_01a1_1** | Eff. 3+1 numu disap | numuCC-like (x3 det) | Enu_reco | 2019b1 | 01a1 | |
| **sbn_numu_disapp_2019b2_01a1_1** | Eff. 3+1 numu disap | numuCC-like (x3 det) | Enu_reco | 2019b2 | 01a1 | |
| **sbn_numu_disapp_2019b2_02a1_1** | Eff. 3+1 numu disap | numuCC-like (x3 det) | Enu_reco | 2019b2 | 02a1 | |
| **sbn_numu_disapp_2019b2_02a2_1** | Eff. 3+1 numu disap | numuCC-like (x3 det) | Enu_reco | 2019b2 | 02a1 | |

MC productions (flux, interaction, detector simulations), the corresponding uncertainty assignments and internal VALOR representations of the uncertainties, and the reconstruction / data reduction event selection codes are important elements used for characterising each fit. Information about the elements used by each VALOR analysis is outlined below.

### Information on SBN productions (simulation, reconstruction and selection) used in VALOR

VALOR uses the following naming scheme for **SBN MC productions** and the reconstructed event samples obtained b
<pre>
           [date][physics model][revision]
     (eg.:  2020              a         1)
</pre>
A summary of all SBN MC productions used is given in the table below.

| SBN pro  | Flux    | GENIE (vrs;tune;err) | SBNCode  | Comments
|----------|---------|----------------------|----------|-----------|
| 2019a1   | configF | v2.12.10; Default+MEC; proposal | v2.2 | `proposal'; last respin of 2019a still in use while establishing this archive on 04/2020 |
| 2019b1   | configF | v2.12.10; Default+MEC; proposal | v2.2 | `modern'; last respin of 2019b still in use while establishing this archive on 04/2020 |
| 2019b2   | configF | v2.12.10; Default+MEC; proposal | v2.2 / gputnam-workshop | `modern'; batch of files made available after the 09/2019 SBN analysis workshop |
| 2020a1   | configF | v3.0.6; G18_10a_02_11a; proposal+MEC | gputnam-workshop0320-gen | `modern'; batch of files made available after the 03/2020 SBN analysis workshop |

- [1] https://cdcvs.fnal.gov/redmine/projects/sbncode/wiki/Fitter_Validation_NuMu_sample: 
SBNCode v2.2, 'modern' and 'proposal'
- [2] https://cdcvs.fnal.gov/redmine/projects/sbn-analysis-group/wiki/How_to_access_Workshop_Osc_samples: 
SBNCode workshop-game samples, modern only from here on

### Information on VALOR/SBN systematic error parameterizations

VALOR uses the following naming scheme for its **SBN systematic error parameterizations**. A number of different *generations* of error parameterizations can exist, each with several versions, each of which can have numerous minor revisons:
<pre>
      [generation][version][revision]
(eg.:          01        a         1)
</pre>

A summary of all error parameterizations implemented in the VALOR SBN analysis is given below.

| Err param | Detector | Flux  | Interaction  | Comments  |
|-----------|----------|-------|--------------|-----------|
| 01a1 | n/a  | CORLIN{loc,flav,Ereco} parameterization of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a) | COV{Ereco} parameterization of the [2015aP x-section error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/XSec-systematics-2015a) | Last version of the 01 parameterization still at use while establishing this table on 04/2020; Used for the 01/2020 Fermilab PAC studies and the associated SBN-OSC WG tech note |
| 02a1 | n/a  | CORLIN{loc,flav,Etrue} parameterization of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a) | CORLIN{Ereco} parameterization of the [2015aP x-section error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/XSec-systematics-2015a) | **Temporary:** Stopgap implementation towards the full 02 parameterization; used at the 03/2020 SBN analysis workshop |
| 02a2 | CORLIN{det,sample,mode,Ereco}, as specified by the [effective 2020a detector error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Detector-systematics-2020a) | as in 02a1 | as in 02a1 | **Temporary:** Adding first version of detector systematics on 02a1 |
| 02b1 | n/a  | CORLIN{loc,flav,Etrue} parameterization of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a)| RESP1D{all} + ad hoc 50% MEC normalisation systematic (**XSEC: REF?**) | |
| 02b2 | CORLIN{det,sample,mode,Ereco}, as specified by the [effective 2020a detector error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Detector-systematics-2020a) | CORLIN{loc,flav,Etrue} parameterization for hadroproduction multi-sim systematics and RESP1D parameterization of optics and hadronic interaction uni-sim systematics of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a) | RESP1D{all} + ad hoc 50% MEC normalisation systematic (**XSEC: REF?**) | |
| 02c1 | n/a  | CORLIN{loc,flav,Etrue} parameterization for hadroproduction multi-sim systematics and RESP1D parameterization of optics and hadronic interaction uni-sim systematics of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a) | RESP1D{all} + ad hoc 50% MEC normalisation systematic (**XSEC: REF?**) | |
| 02c2 | CORLIN{det,sample,mode,Ereco}, as specified by the [effective 2020a detector error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Detector-systematics-2020a) | CORLIN{loc,flav,Etrue} parameterization for hadroproduction multi-sim systematics and RESP1D parameterization of optics and hadronic interaction uni-sim systematics of the [2015a flux error model](https://github.com/VALOR-fit/VALOR-SBN/wiki/Flux-systematics-2015a) | RESP1D{all} + ad hoc 50% MEC normalisation systematic (**XSEC: REF?**) | |

Internal systematic error parameterization methods:
 - **CORLIN{'space'}**: A set of correlated linear responses, each of which is applied on a single bin of the specified 'space' that can be mapped to subsets of kinematic bins for specific MC templates.
 - **RESP1D{'params'}**: Non-linear 1D response functions, each of which is acting on all (or a subset of) kinematic bins of selected MC templates.


