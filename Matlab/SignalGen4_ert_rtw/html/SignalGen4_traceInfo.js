function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Direct Lookup
Table (n-D)1 */
	this.urlHashMap["SignalGen4:139"] = "SignalGen4.c:71,74,85&SignalGen4.h:59&SignalGen4_data.c:22";
	/* <Root>/Direct Lookup
Table (n-D)2 */
	this.urlHashMap["SignalGen4:144"] = "SignalGen4.c:87,90,101&SignalGen4.h:62&SignalGen4_data.c:72";
	/* <Root>/Direct Lookup
Table (n-D)3 */
	this.urlHashMap["SignalGen4:148"] = "SignalGen4.c:115,118,129&SignalGen4.h:65&SignalGen4_data.c:123";
	/* <Root>/Direct Lookup
Table (n-D)4 */
	this.urlHashMap["SignalGen4:149"] = "SignalGen4.c:131,134,145&SignalGen4.h:68&SignalGen4_data.c:172";
	/* <Root>/ePWM7
DAC1 and DAC2 */
	this.urlHashMap["SignalGen4:27"] = "SignalGen4.c:103,215";
	/* <Root>/ePWM8
DAC3 and DAC4 */
	this.urlHashMap["SignalGen4:146"] = "SignalGen4.c:147,390";
	/* <S1>/Data Type
Propagation */
	this.urlHashMap["SignalGen4:137:1"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:137:1";
	/* <S1>/Output */
	this.urlHashMap["SignalGen4:137:4"] = "SignalGen4.c:72,88,116,132,161,167,172,565&SignalGen4.h:53,77&SignalGen4_data.c:226";
	/* <S2>/DAC1 Vrms */
	this.urlHashMap["SignalGen4:171"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:171";
	/* <S2>/DAC2 Vrms */
	this.urlHashMap["SignalGen4:172"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:172";
	/* <S2>/DAC3 Vrms */
	this.urlHashMap["SignalGen4:174"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:174";
	/* <S2>/DAC4 Vrms */
	this.urlHashMap["SignalGen4:176"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:176";
	/* <S2>/Osciloscoppe view */
	this.urlHashMap["SignalGen4:143"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:143";
	/* <S2>/RMS */
	this.urlHashMap["SignalGen4:170"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:170";
	/* <S2>/RMS1 */
	this.urlHashMap["SignalGen4:173"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:173";
	/* <S2>/RMS2 */
	this.urlHashMap["SignalGen4:175"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:175";
	/* <S2>/RMS3 */
	this.urlHashMap["SignalGen4:177"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:177";
	/* <S3>/FixPt
Constant */
	this.urlHashMap["SignalGen4:137:3:2"] = "SignalGen4.c:160&SignalGen4.h:80&SignalGen4_data.c:229";
	/* <S3>/FixPt
Data Type
Duplicate */
	this.urlHashMap["SignalGen4:137:3:3"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:137:3:3";
	/* <S3>/FixPt
Sum1 */
	this.urlHashMap["SignalGen4:137:3:4"] = "SignalGen4.c:159";
	/* <S4>/Constant */
	this.urlHashMap["SignalGen4:137:5:4"] = "SignalGen4.c:168&SignalGen4.h:74&SignalGen4_data.c:223";
	/* <S4>/FixPt
Data Type
Duplicate1 */
	this.urlHashMap["SignalGen4:137:5:2"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:137:5:2";
	/* <S4>/FixPt
Switch */
	this.urlHashMap["SignalGen4:137:5:3"] = "SignalGen4.c:165,176&SignalGen4.h:71&SignalGen4_data.c:220";
	/* <S5>/Bias
offset */
	this.urlHashMap["SignalGen4:165"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:165";
	/* <S5>/Gain
to volts */
	this.urlHashMap["SignalGen4:155"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:155";
	/* <S6>/Rate Transition */
	this.urlHashMap["SignalGen4:163"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:163";
	/* <S6>/To Workspace */
	this.urlHashMap["SignalGen4:159"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:159";
	/* <S6>/ZOH
ADC simulation */
	this.urlHashMap["SignalGen4:162"] = "msg=rtwMsg_reducedBlock&block=SignalGen4:162";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "SignalGen4"};
	this.sidHashMap["SignalGen4"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "SignalGen4:137"};
	this.sidHashMap["SignalGen4:137"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "SignalGen4:182"};
	this.sidHashMap["SignalGen4:182"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "SignalGen4:137:3"};
	this.sidHashMap["SignalGen4:137:3"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "SignalGen4:137:5"};
	this.sidHashMap["SignalGen4:137:5"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<S5>"] = {sid: "SignalGen4:187"};
	this.sidHashMap["SignalGen4:187"] = {rtwname: "<S5>"};
	this.rtwnameHashMap["<S6>"] = {sid: "SignalGen4:196"};
	this.sidHashMap["SignalGen4:196"] = {rtwname: "<S6>"};
	this.rtwnameHashMap["<Root>/Counter Limited"] = {sid: "SignalGen4:137"};
	this.sidHashMap["SignalGen4:137"] = {rtwname: "<Root>/Counter Limited"};
	this.rtwnameHashMap["<Root>/Direct Lookup Table (n-D)1"] = {sid: "SignalGen4:139"};
	this.sidHashMap["SignalGen4:139"] = {rtwname: "<Root>/Direct Lookup Table (n-D)1"};
	this.rtwnameHashMap["<Root>/Direct Lookup Table (n-D)2"] = {sid: "SignalGen4:144"};
	this.sidHashMap["SignalGen4:144"] = {rtwname: "<Root>/Direct Lookup Table (n-D)2"};
	this.rtwnameHashMap["<Root>/Direct Lookup Table (n-D)3"] = {sid: "SignalGen4:148"};
	this.sidHashMap["SignalGen4:148"] = {rtwname: "<Root>/Direct Lookup Table (n-D)3"};
	this.rtwnameHashMap["<Root>/Direct Lookup Table (n-D)4"] = {sid: "SignalGen4:149"};
	this.sidHashMap["SignalGen4:149"] = {rtwname: "<Root>/Direct Lookup Table (n-D)4"};
	this.rtwnameHashMap["<Root>/Simulation view"] = {sid: "SignalGen4:182"};
	this.sidHashMap["SignalGen4:182"] = {rtwname: "<Root>/Simulation view"};
	this.rtwnameHashMap["<Root>/ePWM7 DAC1 and DAC2"] = {sid: "SignalGen4:27"};
	this.sidHashMap["SignalGen4:27"] = {rtwname: "<Root>/ePWM7 DAC1 and DAC2"};
	this.rtwnameHashMap["<Root>/ePWM8 DAC3 and DAC4"] = {sid: "SignalGen4:146"};
	this.sidHashMap["SignalGen4:146"] = {rtwname: "<Root>/ePWM8 DAC3 and DAC4"};
	this.rtwnameHashMap["<S1>/Data Type Propagation"] = {sid: "SignalGen4:137:1"};
	this.sidHashMap["SignalGen4:137:1"] = {rtwname: "<S1>/Data Type Propagation"};
	this.rtwnameHashMap["<S1>/Force to be scalar"] = {sid: "SignalGen4:137:2"};
	this.sidHashMap["SignalGen4:137:2"] = {rtwname: "<S1>/Force to be scalar"};
	this.rtwnameHashMap["<S1>/Increment Real World"] = {sid: "SignalGen4:137:3"};
	this.sidHashMap["SignalGen4:137:3"] = {rtwname: "<S1>/Increment Real World"};
	this.rtwnameHashMap["<S1>/Output"] = {sid: "SignalGen4:137:4"};
	this.sidHashMap["SignalGen4:137:4"] = {rtwname: "<S1>/Output"};
	this.rtwnameHashMap["<S1>/Wrap To Zero"] = {sid: "SignalGen4:137:5"};
	this.sidHashMap["SignalGen4:137:5"] = {rtwname: "<S1>/Wrap To Zero"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "SignalGen4:137:6"};
	this.sidHashMap["SignalGen4:137:6"] = {rtwname: "<S1>/y"};
	this.rtwnameHashMap["<S2>/DAC1"] = {sid: "SignalGen4:183"};
	this.sidHashMap["SignalGen4:183"] = {rtwname: "<S2>/DAC1"};
	this.rtwnameHashMap["<S2>/DAC2"] = {sid: "SignalGen4:184"};
	this.sidHashMap["SignalGen4:184"] = {rtwname: "<S2>/DAC2"};
	this.rtwnameHashMap["<S2>/DAC3"] = {sid: "SignalGen4:185"};
	this.sidHashMap["SignalGen4:185"] = {rtwname: "<S2>/DAC3"};
	this.rtwnameHashMap["<S2>/DAC4"] = {sid: "SignalGen4:186"};
	this.sidHashMap["SignalGen4:186"] = {rtwname: "<S2>/DAC4"};
	this.rtwnameHashMap["<S2>/DAC1 Vrms"] = {sid: "SignalGen4:171"};
	this.sidHashMap["SignalGen4:171"] = {rtwname: "<S2>/DAC1 Vrms"};
	this.rtwnameHashMap["<S2>/DAC2 Vrms"] = {sid: "SignalGen4:172"};
	this.sidHashMap["SignalGen4:172"] = {rtwname: "<S2>/DAC2 Vrms"};
	this.rtwnameHashMap["<S2>/DAC3 Vrms"] = {sid: "SignalGen4:174"};
	this.sidHashMap["SignalGen4:174"] = {rtwname: "<S2>/DAC3 Vrms"};
	this.rtwnameHashMap["<S2>/DAC4 Vrms"] = {sid: "SignalGen4:176"};
	this.sidHashMap["SignalGen4:176"] = {rtwname: "<S2>/DAC4 Vrms"};
	this.rtwnameHashMap["<S2>/Demux"] = {sid: "SignalGen4:154"};
	this.sidHashMap["SignalGen4:154"] = {rtwname: "<S2>/Demux"};
	this.rtwnameHashMap["<S2>/Osciloscoppe view"] = {sid: "SignalGen4:143"};
	this.sidHashMap["SignalGen4:143"] = {rtwname: "<S2>/Osciloscoppe view"};
	this.rtwnameHashMap["<S2>/RMS"] = {sid: "SignalGen4:170"};
	this.sidHashMap["SignalGen4:170"] = {rtwname: "<S2>/RMS"};
	this.rtwnameHashMap["<S2>/RMS1"] = {sid: "SignalGen4:173"};
	this.sidHashMap["SignalGen4:173"] = {rtwname: "<S2>/RMS1"};
	this.rtwnameHashMap["<S2>/RMS2"] = {sid: "SignalGen4:175"};
	this.sidHashMap["SignalGen4:175"] = {rtwname: "<S2>/RMS2"};
	this.rtwnameHashMap["<S2>/RMS3"] = {sid: "SignalGen4:177"};
	this.sidHashMap["SignalGen4:177"] = {rtwname: "<S2>/RMS3"};
	this.rtwnameHashMap["<S2>/Scale to 3.3 Volts"] = {sid: "SignalGen4:187"};
	this.sidHashMap["SignalGen4:187"] = {rtwname: "<S2>/Scale to 3.3 Volts"};
	this.rtwnameHashMap["<S2>/Subsystem"] = {sid: "SignalGen4:196"};
	this.sidHashMap["SignalGen4:196"] = {rtwname: "<S2>/Subsystem"};
	this.rtwnameHashMap["<S3>/u"] = {sid: "SignalGen4:137:3:1"};
	this.sidHashMap["SignalGen4:137:3:1"] = {rtwname: "<S3>/u"};
	this.rtwnameHashMap["<S3>/FixPt Constant"] = {sid: "SignalGen4:137:3:2"};
	this.sidHashMap["SignalGen4:137:3:2"] = {rtwname: "<S3>/FixPt Constant"};
	this.rtwnameHashMap["<S3>/FixPt Data Type Duplicate"] = {sid: "SignalGen4:137:3:3"};
	this.sidHashMap["SignalGen4:137:3:3"] = {rtwname: "<S3>/FixPt Data Type Duplicate"};
	this.rtwnameHashMap["<S3>/FixPt Sum1"] = {sid: "SignalGen4:137:3:4"};
	this.sidHashMap["SignalGen4:137:3:4"] = {rtwname: "<S3>/FixPt Sum1"};
	this.rtwnameHashMap["<S3>/y"] = {sid: "SignalGen4:137:3:5"};
	this.sidHashMap["SignalGen4:137:3:5"] = {rtwname: "<S3>/y"};
	this.rtwnameHashMap["<S4>/U"] = {sid: "SignalGen4:137:5:1"};
	this.sidHashMap["SignalGen4:137:5:1"] = {rtwname: "<S4>/U"};
	this.rtwnameHashMap["<S4>/Constant"] = {sid: "SignalGen4:137:5:4"};
	this.sidHashMap["SignalGen4:137:5:4"] = {rtwname: "<S4>/Constant"};
	this.rtwnameHashMap["<S4>/FixPt Data Type Duplicate1"] = {sid: "SignalGen4:137:5:2"};
	this.sidHashMap["SignalGen4:137:5:2"] = {rtwname: "<S4>/FixPt Data Type Duplicate1"};
	this.rtwnameHashMap["<S4>/FixPt Switch"] = {sid: "SignalGen4:137:5:3"};
	this.sidHashMap["SignalGen4:137:5:3"] = {rtwname: "<S4>/FixPt Switch"};
	this.rtwnameHashMap["<S4>/Y"] = {sid: "SignalGen4:137:5:5"};
	this.sidHashMap["SignalGen4:137:5:5"] = {rtwname: "<S4>/Y"};
	this.rtwnameHashMap["<S5>/In1"] = {sid: "SignalGen4:188"};
	this.sidHashMap["SignalGen4:188"] = {rtwname: "<S5>/In1"};
	this.rtwnameHashMap["<S5>/In2"] = {sid: "SignalGen4:189"};
	this.sidHashMap["SignalGen4:189"] = {rtwname: "<S5>/In2"};
	this.rtwnameHashMap["<S5>/In3"] = {sid: "SignalGen4:190"};
	this.sidHashMap["SignalGen4:190"] = {rtwname: "<S5>/In3"};
	this.rtwnameHashMap["<S5>/In4"] = {sid: "SignalGen4:191"};
	this.sidHashMap["SignalGen4:191"] = {rtwname: "<S5>/In4"};
	this.rtwnameHashMap["<S5>/Bias offset"] = {sid: "SignalGen4:165"};
	this.sidHashMap["SignalGen4:165"] = {rtwname: "<S5>/Bias offset"};
	this.rtwnameHashMap["<S5>/Gain to volts"] = {sid: "SignalGen4:155"};
	this.sidHashMap["SignalGen4:155"] = {rtwname: "<S5>/Gain to volts"};
	this.rtwnameHashMap["<S5>/Mux"] = {sid: "SignalGen4:151"};
	this.sidHashMap["SignalGen4:151"] = {rtwname: "<S5>/Mux"};
	this.rtwnameHashMap["<S5>/Out1"] = {sid: "SignalGen4:192"};
	this.sidHashMap["SignalGen4:192"] = {rtwname: "<S5>/Out1"};
	this.rtwnameHashMap["<S6>/ADC"] = {sid: "SignalGen4:197"};
	this.sidHashMap["SignalGen4:197"] = {rtwname: "<S6>/ADC"};
	this.rtwnameHashMap["<S6>/Rate Transition"] = {sid: "SignalGen4:163"};
	this.sidHashMap["SignalGen4:163"] = {rtwname: "<S6>/Rate Transition"};
	this.rtwnameHashMap["<S6>/To Workspace"] = {sid: "SignalGen4:159"};
	this.sidHashMap["SignalGen4:159"] = {rtwname: "<S6>/To Workspace"};
	this.rtwnameHashMap["<S6>/ZOH ADC simulation"] = {sid: "SignalGen4:162"};
	this.sidHashMap["SignalGen4:162"] = {rtwname: "<S6>/ZOH ADC simulation"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
