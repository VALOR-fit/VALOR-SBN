// Relevant set of numuCC efficiency systematics
//
// #    Param  Beam   Detector  Sample        Mode            Reco energy range (GeV)
// -----------------------------------------------------------------------------
//  0   f0     FHC    SBND      numuCC-like   signal/numuCC   0.0 - 0.2
//  1   f1     FHC    SBND      numuCC-like   signal/numuCC   0.2 - 0.4
//  2   f2     FHC    SBND      numuCC-like   signal/numuCC   0.4 - 0.6
//  3   f3     FHC    SBND      numuCC-like   signal/numuCC   0.6 - 0.8
//  4   f4     FHC    SBND      numuCC-like   signal/numuCC   0.8 - 1.0
//  5   f5     FHC    SBND      numuCC-like   signal/numuCC   1.0 - 1.5
//  6   f6     FHC    SBND      numuCC-like   signal/numuCC   1.5 - 2.0
//  7   f7     FHC    SBND      numuCC-like   signal/numuCC   2.0 - oo
//  8   f8     FHC    SBND      numuCC-like   bkg/NC          0.0 - 0.2
//  9   f9     FHC    SBND      numuCC-like   bkg/NC          0.2 - 0.4
// 10  f10     FHC    SBND      numuCC-like   bkg/NC          0.4 - 0.6
// 11  f11     FHC    SBND      numuCC-like   bkg/NC          0.6 - 0.8
// 12  f12     FHC    SBND      numuCC-like   bkg/NC          0.8 - 1.0
// 13  f13     FHC    SBND      numuCC-like   bkg/NC          1.0 - oo
// 14  f14     FHC    SBND      numuCC-like   bkg/Dirt        0.0 - oo
// 15  f15     FHC    SBND      numuCC-like   bkg/Cosmics     0.0 - oo
// 16  f146    FHC    ICARUS    numuCC-like   signal/numuCC   0.0 - 0.2
// 17  f147    FHC    ICARUS    numuCC-like   signal/numuCC   0.2 - 0.4
// 18  f148    FHC    ICARUS    numuCC-like   signal/numuCC   0.4 - 0.6
// 19  f149    FHC    ICARUS    numuCC-like   signal/numuCC   0.6 - 0.8
// 20  f150    FHC    ICARUS    numuCC-like   signal/numuCC   0.8 - 1.0
// 21  f151    FHC    ICARUS    numuCC-like   signal/numuCC   1.0 - 1.5
// 22  f152    FHC    ICARUS    numuCC-like   signal/numuCC   1.5 - 2.0
// 23  f153    FHC    ICARUS    numuCC-like   signal/numuCC   2.0 - oo
// 24  f154    FHC    ICARUS    numuCC-like   bkg/NC          0.0 - 0.2
// 25  f155    FHC    ICARUS    numuCC-like   bkg/NC          0.2 - 0.4
// 26  f156    FHC    ICARUS    numuCC-like   bkg/NC          0.4 - 0.6
// 27  f157    FHC    ICARUS    numuCC-like   bkg/NC          0.6 - 0.8
// 28  f158    FHC    ICARUS    numuCC-like   bkg/NC          0.8 - 1.0
// 29  f159    FHC    ICARUS    numuCC-like   bkg/NC          1.0 - oo
// 30  f160    FHC    ICARUS    numuCC-like   bkg/Dirt        0.0 - oo
// 31  f161    FHC    ICARUS    numuCC-like   bkg/Cosmics     0.0 - oo
//
//

const int kNSystNuMuCC = 114;

enum kSystNuECC {
kf16= 0,
kf17= 1,
kf18= 2,
kf19= 3,
kf20= 4,
kf21= 5,
kf22= 6,
kf23= 7,
kf24= 8,
kf25= 9,
kf26= 10,
kf27= 11,
kf28= 12,
kf29= 13,
kf30= 14,
kf31= 15,
kf32= 16,
kf33= 17,
kf34= 18,
kf35= 19,
kf36= 20,
kf37= 21,
kf38= 22,
kf39= 23,
kf40= 24,
kf41= 25,
kf42= 26,
kf43= 27,
kf44= 28,
kf45= 29,
kf46= 30,
kf47= 31,
kf48= 32,
kf49= 33,
kf50= 34,
kf51= 35,
kf52= 36,
kf53= 37,
kf54= 38,
kf55= 39,
kf56= 40,
kf57= 41,
kf58= 42,
kf59= 43,
kf60= 44,
kf61= 45,
kf62= 46,
kf63= 47,
kf64= 48,
kf65= 49,
kf66= 50,
kf67= 51,
kf68= 52,
kf69= 53,
kf70= 54,
kf71= 55,
kf72= 56,
kf162 = 57,
kf163 = 58,
kf164 = 59,
kf165 = 60,
kf166 = 61,
kf167 = 62,
kf168 = 63,
kf169 = 64,
kf170 = 65,
kf171 = 66,
kf172 = 67,
kf173 = 68,
kf174 = 69,
kf175 = 70,
kf176 = 71,
kf177 = 72,
kf178 = 73,
kf179 = 74,
kf180 = 75,
kf181 = 76,
kf182 = 77,
kf183 = 78,
kf184 = 79,
kf185 = 80,
kf186 = 81,
kf187 = 82,
kf188 = 83,
kf189 = 84,
kf190 = 85,
kf191 = 86,
kf192 = 87,
kf193 = 88,
kf194 = 89,
kf195 = 90,
kf196 = 91,
kf197 = 92,
kf198 = 93,
kf199 = 94,
kf200 = 95,
kf201 = 96,
kf202 = 97,
kf203 = 98,
kf204 = 99,
kf205 = 100,
kf206 = 101,
kf207 = 102,
kf208 = 103,
kf209 = 104,
kf210 = 105,
kf211 = 106,
kf212 = 107,
kf213 = 108,
kf214 = 109,
kf215 = 110,
kf216 = 111,
kf217 = 112,
kf218 = 113
} kSystNuMuCC_t;

// Creates matrices with fully correlated error
void fully_correlated_only(
  double cor_frac_err            // input correlated fractional error
);
// Creates matrices with fully correlated error + uniform uncorrelated error
// set separately for two _contiguous_ bin groups (corresponding to different detectors)
void fully_correlated_and_uniform_uncorrelated_per_detector(
  double cor_frac_err,           // input correlated fractional error
  double uncor_frac_err_sbnd,    // input uncorrelated fractional error for bin group 1
  int    min_bin_sbnd,           // minimum bin for group 1
  int    max_bin_sbnd,           // maximum bin for group 1
  double uncor_frac_err_icarus,  // input uncorrelated fractional error for bin group 2
  int    min_bin_icarus,         // minimum bin for group 2
  int    max_bin_icarus          // maximum bin for group 2
);
// Creates matrices with fully correlated error + uniform uncorrelated error for
// the bulk of bins + a separately defined uniform uncorrelated error for a
// narrowly-define set of bins
// (eg  SBND low energy numuCC signal, or ICARUS NC bkg, or SBND+ICARUS NC bkg)
void fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
  double cor_frac_err,              // input correlated fractional error
  double uncor_frac_err_bulk,       // input uncorrelated fractional error for bulk of bins
  double uncor_frac_err_target = 0, // input uncorrelated fractional error for target group of bins under investigation
  int    min_bin_target1 = -1,      // minimum bin for target group of bins (1)
  int    max_bin_target1 = -1,      // maximum bin for target group of bins (1)
  int    min_bin_target2 = -1,      // minimum bin for target group of bins (2)
  int    max_bin_target2 = -1,      // maximum bin for target group of bins (2)
  const char * label = ""           // label for target group of bins
);

//..................................................................................
void eff_err_matrix_nue(void)
{
  // Create "type 1" error matrices
  // Explore impact of different fully correlated (bin-to-bin) errors
  fully_correlated_only(0.010);
  fully_correlated_only(0.020);
  fully_correlated_only(0.050);
  fully_correlated_only(0.100);

  // Create "type 2" error matrices
  // Fix fully correlated error to x%, and explore the impact of different
  // values of uniform (in each of 2 groups of bins) uncorrelated error
  // First group is SBND, second group is ICARUS
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.005,kf16,kf72, 0.005,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.005,kf16,kf72, 0.010,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.005,kf16,kf72, 0.020,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.010,kf16,kf72, 0.005,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.010,kf16,kf72, 0.010,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.010,kf16,kf72, 0.020,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.020,kf16,kf72, 0.005,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.020,kf16,kf72, 0.010,kf162,kf218);
  fully_correlated_and_uniform_uncorrelated_per_detector(
      0.020, 0.020,kf16,kf72, 0.020,kf162,kf218);

  /*
  // Create "type 3" error matrices
  // Fix fully correlated error to x%, fix the bulk of the uncorrelated error
  // to y%, and and explore the impact of a worse uniform uncorrelated error in
  // a single, narrowly-defined category of bins
  // (eg SBND low energy numuCC signal, or ICARUS NC bkg)
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf0,   kf2,      -1,    -1,  "sbndlowEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf3,   kf4,      -1,    -1,  "sbndpeakEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf5,   kf7,      -1,    -1,  "sbndhighEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf8,   kf13,     -1,    -1,  "sbndNCbkg");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf146, kf148,    -1,    -1,  "icaruslowEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf149, kf150,    -1,    -1,  "icaruspeakEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf151, kf153,    -1,    -1,  "icarushighEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf154, kf159,    -1,    -1,  "icarusNCbkg");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf0,   kf2,   kf146, kf148,  "alllowEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf3,   kf4,   kf149, kf150,  "allpeakEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf5,   kf7,   kf151, kf153,  "allhighEnumuCC");
  fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
    0.020, 0.005, 0.020, kf8,   kf13,  kf154, kf159,  "allNCbkg");
 */
}
//..................................................................................
void fully_correlated_only(double cor_frac_err)
{
  TMatrixT<double> frac_cov_corr   (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_uncorr (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_total  (kNSystNuMuCC,kNSystNuMuCC);

  for(int i=0; i<kNSystNuMuCC; i++) {
    for(int j=0; j<kNSystNuMuCC; j++) {
      frac_cov_corr  (i,j) = TMath::Power(cor_frac_err,2.);
      frac_cov_uncorr(i,j) = 0.;
      frac_cov_total (i,j) = frac_cov_corr(i,j);
    }//j
  }//i

  const char * filename =
   Form("efficiency_error_matrix_%dx%d_type1_cor%.2fpct.root",
         kNSystNuMuCC,kNSystNuMuCC,100.*cor_frac_err);

  TFile f(filename,"recreate");
  frac_cov_corr.  Write( "frac_cov_corr"   );
  frac_cov_uncorr.Write( "frac_cov_uncorr" );
  frac_cov_total. Write( "frac_cov_total"  );
  f.Close();
}
//..................................................................................
void fully_correlated_and_uniform_uncorrelated_per_detector(
  double cor_frac_err,
  double uncor_frac_err_1, int min_bin_1, int max_bin_1, /* sbnd   */
  double uncor_frac_err_2, int min_bin_2, int max_bin_2  /* icarus */
)
{
  TMatrixT<double> frac_cov_corr   (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_uncorr (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_total  (kNSystNuMuCC,kNSystNuMuCC);

  // set input correlated error and initialise other errors
  for(int i=0; i<kNSystNuMuCC; i++) {
    for(int j=0; j<kNSystNuMuCC; j++) {
      frac_cov_corr  (i,j) = TMath::Power(cor_frac_err,2.);
      frac_cov_uncorr(i,j) = 0.;
      frac_cov_total (i,j) = 0;
    }//j
  }//i
  // set input uncorrelated error for bin group 1
  for(int i=min_bin_1; i<=max_bin_1; i++) {
    frac_cov_uncorr(i,i) = TMath::Power(uncor_frac_err_1,2.);
  }//i
  // set input uncorrelated error for bin group 2
  for(int i=min_bin_2; i<=max_bin_2; i++) {
    frac_cov_uncorr(i,i) = TMath::Power(uncor_frac_err_2,2.);
  }//i
  // set total error
  frac_cov_total = frac_cov_corr + frac_cov_uncorr;

  const char * filename =
   Form("efficiency_error_matrix_%dx%d_type2_cor%.2fpct_sbnduncor%.2fpct_icarusuncor%.2fpct.root",
         kNSystNuMuCC,kNSystNuMuCC,
         100.*cor_frac_err, 100.*uncor_frac_err_1,100.*uncor_frac_err_2);

  TFile f(filename,"recreate");
  frac_cov_corr.  Write( "frac_cov_corr"   );
  frac_cov_uncorr.Write( "frac_cov_uncorr" );
  frac_cov_total. Write( "frac_cov_total"  );
  f.Close();
}
//..................................................................................
/*
void fully_correlated_and_uniform_bulk_uncorrelated_and_uniform_uncorrelated_for_target_group(
  double cor_frac_err,
  double uncor_frac_err_bulk,
  double uncor_frac_err_target,
  int    min_bin_target1,
  int    max_bin_target1,
  int    min_bin_target2,
  int    max_bin_target2,
  const char * label
)
{
  TMatrixT<double> frac_cov_corr   (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_uncorr (kNSystNuMuCC,kNSystNuMuCC);
  TMatrixT<double> frac_cov_total  (kNSystNuMuCC,kNSystNuMuCC);

  // set input correlated error and initialise other errors
  for(int i=0; i<kNSystNuMuCC; i++) {
    for(int j=0; j<kNSystNuMuCC; j++) {
      frac_cov_corr  (i,j) = TMath::Power(cor_frac_err,2.);
      frac_cov_uncorr(i,j) = 0.;
      frac_cov_total (i,j) = 0;
    }//j
  }//i
  // set bulk uncorrelated error
  for(int i=0; i<kNSystNuMuCC; i++) {
    frac_cov_uncorr(i,i) = TMath::Power(uncor_frac_err_bulk,2.);
  }//i
  // override the bulk uncorrelated error for target set of bins
  if(min_bin_target1>-1 && max_bin_target1>=min_bin_target1) {
    for(int i=min_bin_target1; i<=max_bin_target1; i++) {
      frac_cov_uncorr(i,i) = TMath::Power(uncor_frac_err_target,2.);
    }//i
  }
  if(min_bin_target2>-1 && max_bin_target2>=min_bin_target2) {
    for(int i=min_bin_target2; i<=max_bin_target2; i++) {
      frac_cov_uncorr(i,i) = TMath::Power(uncor_frac_err_target,2.);
    }//i
  }
  // set total error
  frac_cov_total = frac_cov_corr + frac_cov_uncorr;

  const char * filename =
   Form("efficiency_error_matrix_%dx%d_type3_cor%.2fpct_bulkuncor%.2fpct_%suncor%.2fpct.root",
         kNSystNuMuCC,kNSystNuMuCC,
         100.*cor_frac_err, 100.*uncor_frac_err_bulk,label,100.*uncor_frac_err_target);

  TFile f(filename,"recreate");
  frac_cov_corr.  Write( "frac_cov_corr"   );
  frac_cov_uncorr.Write( "frac_cov_uncorr" );
  frac_cov_total. Write( "frac_cov_total"  );
  f.Close();
}
*/
//..................................................................................
