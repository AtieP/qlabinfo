#include "qlabinfo.h"

#include <stddef.h>
#include <stdlib.h>

#define logbook_url_m(name) "https://be-op-logbook.web.cern.ch/elogbook-server/#/logbook?logbookId=" name
#define image_url(name) "https://vistar-capture.web.cern.ch/vistar-capture/" name
#define doc_url(name) "https://op-webtools.web.cern.ch/Vistar/Doc/" name ".pdf"

struct cern_vistar cern_vistars[] =
{
	/*
		1st: name, image url, logbook url, documentation url
		2nd: refresh rate, extended refresh rate
	*/
	{
		"ADE", image_url("ade.png"), logbook_url_m("1321"), NULL,
		1100, 3000
	},
	{
		"Awake", image_url("awake.png"), NULL, NULL,
		2000, 5000
	},
	{
		"Awake Plasma", image_url("awakeplasma.png"), NULL, NULL,
		1000, 1000
	},
	{
		"Awake Proton", image_url("awakeproton.png"), NULL, NULL,
		1000, 1000
	},
	{
		"CLEAR Operation", image_url("cleargen.png"), logbook_url_m("100"), doc_url("CTF3Operation"),
		1100, 6000
	},
	{
		"CPS", image_url("cps.png"), logbook_url_m("683"), NULL,
		1100, 6000
	},
	{
		"CPS BLM", image_url("cpsblm.png"), logbook_url_m("683"), NULL,
		500, 5000
	},
	{
		"CPS EAST Area", image_url("pea.png"), logbook_url_m("683"), NULL,
		1100, 6000
	},
	{
		"CPS Spare", image_url("cps2.png"), NULL, NULL,
		2000, 2000
	},
	{
		"ELENA", image_url("elena.png"), NULL, NULL,
		1200, 5000
	},
	{
		"GPS", image_url("gps.png"), logbook_url_m("603"), NULL,
		1100, 6000
	},
	{
		"HRS", image_url("hrs.png"), logbook_url_m("605"), NULL,
		1100, 6000
	},
	{
		"LEIR", image_url("leir.png"), logbook_url_m("642"), doc_url("LEIR"),
		1100, 6000
	},
	{
		"LHC BLM Abort Gap", image_url("lhcabortgap.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC BLM Diamond", image_url("lhcdiamond.png"), logbook_url_m("322"), doc_url("LHCBLMDiamond"),
		1100, 6000
	},
	{
		"LHC BSRT", image_url("lhcbsrt.png"), logbook_url_m("322"), doc_url("LHCBSRT"),
		1100, 6000
	},
	{
		"LHC Beam Dump", image_url("lhcbds.png"), logbook_url_m("322"), NULL,
		2000, 6000
	},
	{
		"LHC CMS Experiment", "http://cmsoms.cern.ch/agg/api/v1/page1/image.png", logbook_url_m("322"), NULL,
		15000, 15000
	},
	{
		"LHC Collimator Beam 1", image_url("lhccolli1.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Collimator Beam 2", image_url("lhccolli2.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Collimator TL", image_url("lhcolli3.png"), NULL, NULL,
		2000, 5000
	},
	{
		"LHC Collimators Summary", image_url("lhcolli.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Configuration", image_url("lhcconfig.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Coordination", image_url("lhccoord.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Cryogenics", image_url("lhc2.png"), logbook_url_m("322"), NULL,
		8000, 10000
	},
	{
		"LHC Exp Magnets", image_url("lhcexpmag.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Luminosity", image_url("lhclumi.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"LHC Operation", image_url("lhc3.png"), logbook_url_m("322"), NULL,
		5000, 5000
	},
	{
		"LHC Page 1", image_url("lhc1.png"), logbook_url_m("322"), doc_url("LHC1"),
		8000, 10000
	},
	{
		"LHC RF Timing", image_url("lhcrftiming.png"), NULL, NULL,
		2000, 2000
	},
	{
		"LHC Roman Pots", image_url("lhcromanpots.png"), logbook_url_m("322"), NULL,
		2000, 2000
	},
	{
		"LHCf Experiment", image_url("lhcf.png"), logbook_url_m("322"), NULL,
		1100, 6000
	},
	{
		"Linac 3", image_url("ln3.png"), logbook_url_m("21"), doc_url("Linac3"),
		1200, 5000
	},
	{
		"Linac 4", image_url("ln4.png"), logbook_url_m("221"), NULL,
		1000, 1000
	},
	{
		"Linac II", image_url("lin.png"), logbook_url_m("21"), NULL,
		1100, 6000
	},
	{
		"PSB", image_url("psb.png"), logbook_url_m("503"), NULL,
		1100, 6000
	},
	{
		"PSB BLM", image_url("psbblm.png"), logbook_url_m("503"), NULL,
		1200, 10000
	},
	{
		"SPS BSRT", image_url("spsbsrt.png"), logbook_url_m("424"), NULL,
		2000, 5000
	},
	{
		"SPS BT", image_url("spsbt.png"), logbook_url_m("424"), NULL,
		5000, 10000
	},
	{
		"SPS Fast BCT", image_url("spsbctf.png"), logbook_url_m("424"), NULL,
		1200, 7000
	},
	{
		"SPS LARGER 1", image_url("larger1.png"), logbook_url_m("424"), doc_url("LARGER1"),
		1100, 6000
	},
	{
		"SPS LARGER 2", image_url("larger2.png"), logbook_url_m("322"), doc_url("LARGER2"),
		1100, 6000
	},
	{
		"SPS LARGER 3", image_url("larger3.png"), logbook_url_m("424"), doc_url("LARGER3"),
		1100, 6000
	},
	{
		"SPS LARGER 4", image_url("larger4.png"), logbook_url_m("424"), doc_url("LARGER4"),
		1100, 6000
	},
	{
		"SPS Page 1", image_url("sps1.png"), logbook_url_m("424"), doc_url("SPS1"),
		1200, 7000
	},
	{
		"T9 BLFS", image_url("t9blfs.png"), NULL, NULL,
		3000, 3000
	}
};

size_t cern_vistars_amount = sizeof(cern_vistars)
				/ sizeof(struct cern_vistar);


