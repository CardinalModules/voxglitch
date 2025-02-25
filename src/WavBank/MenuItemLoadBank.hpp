struct MenuItemLoadBank : MenuItem
{
	WavBank *module;

  void onAction(const event::Action &e) override
	{
    #ifdef USING_CARDINAL_NOT_RACK
    		WavBank *module = this->module;
    		async_dialog_filebrowser(false, NULL, module->samples_root_dir.c_str(), "Load sample", [module](char* path) {
    			if (path) {
    				if (char *rpath = strrchr(path, CARDINAL_OS_SEP))
    					*rpath = '\0';
    				pathSelected(module, std::string(path));
    				free(path);
    			}
    		});
    #else
    		pathSelected(module, module->selectPathVCV());
    #endif
	}

  static void pathSelected(WavBank *module, std::string path)
	{
		if (path != "")
		{
			module->load_samples_from_path(path);
			module->path = path;
      module->setRoot(path);
		}
	}

  /*
	void onAction(const event::Action &e) override
	{
		const std::string dir = wav_bank_module->rootDir;
#ifdef USING_CARDINAL_NOT_RACK
		WavBank *wav_bank_module = this->wav_bank_module;
		async_dialog_filebrowser(false, dir.c_str(), text.c_str(), [wav_bank_module](char* path) {
			if (path) {
				if (char *rpath = strrchr(path, CARDINAL_OS_SEP))
					*rpath = '\0';
				pathSelected(wav_bank_module, path);
			}
		});
#else
		char *path = osdialog_file(OSDIALOG_OPEN_DIR, dir.c_str(), NULL, NULL);
		pathSelected(wav_bank_module, path);
#endif
	}

	static void pathSelected(WavBank *wav_bank_module, char *path)
	{
		if (path)
		{
			wav_bank_module->load_samples_from_path(path);
			wav_bank_module->path = path;
			free(path);
		}
	}
  */
};
