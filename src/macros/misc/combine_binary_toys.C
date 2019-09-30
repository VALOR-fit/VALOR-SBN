//
// ------------------------------------------------------------------------------------------------
// Combine binary toy files, which are assumed to be different only by a single number (specified by '[X]' in
// the input file name). e.g. if you have the files batch0/toys.bin and batch1/toys.bin, specify the input
// as "batch[X]/toys.bin".
// This also assumes a fixed number of toys per input file.
//
// TODO: The output needs testing
//
// Francis Bench
// Sept. 2019
// ------------------------------------------------------------------------------------------------
//

//___________________________________________________________________________
void combine_binary_toys(
  const char * config_file  = "analysis/t2k_analysis_configuration_oa2018_run1-9d_v1_postfit.xml",
  const char * file_pattern = "batch[X]/migrated_run1-9d_fc_normal_cpv_reactor_0_1_10000.bin",
  const int    batch_first  = 0,
  const int    batch_last   = 3,        // Inclusive range
  const int    n_toys_file  = 10000,
  const char * out_tag      = "migrated_run1-9d_fc_normal_cpv_reactor_0_1_40k_combined.bin",
  const char * opt          = "pdft",
  const bool   is_data      = false,    // If true, treats the toys as instances of GSSFD. If false, treats toys as instances of GSSFM
  const bool   stat_fluct   = true      // For data only
)
{
    CompoundFitElements* elements = new CompoundFitElements();
    elements->Read(util::CompleteConfigPath(config_file));
    FitModelABC* model = elements->FitModel();
    FitDataABC* data = elements->FitData();

    std::ofstream stream_out(out_tag, std::ios::binary | std::ios::out);

    // Work out the file names to read from and loop over files
    for(int ibatch = batch_first; ibatch <= batch_last; ++ibatch) {
        // Get file name
        TString filename(file_pattern);
        filename.ReplaceAll("[X]", TString::Format("%d", ibatch));
        std::cout << "Reading from file [" << filename.Data() << "]" << std::endl;

        std::ifstream stream_in = std::ifstream(filename.Data(), std::ios::binary | std::ios::in);
        if(!stream_in.is_open()) {
            std::cout << "ERROR: Could not find file [" << filename.Data() << "]" << std::endl;
        }
        for(int itoy = 0; itoy < n_toys_file; ++itoy) {
            if(!stream_in.good()) {
                std::cout << "ERROR: Something went wrong when reading the input stream. Reached toy #" << itoy << std::endl;
            }
            model->Read(stream_in , opt);
            // TODO: data->Write(std::ofstream, ...) is not yet implemented
//            if(is_data) {
//                data->Generate(model, stat_fluct, opt);
//                data->Write(stream_out, opt);
//            }
//            else {
             model->Write(stream_out, opt);
//            }
        }
        stream_in.close();
    }
    stream_out.close();
    std::cout << "Done!" << std::endl;
}