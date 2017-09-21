function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Constant */
	this.urlHashMap["SignalGen_rx:221"] = "SignalGen_rx.c:105,149,205,249&SignalGen_rx.h:84&SignalGen_rx_data.c:221";
	/* <Root>/DAC1 Lookup Table */
	this.urlHashMap["SignalGen_rx:139"] = "SignalGen_rx.c:81,84,106,109&SignalGen_rx.h:71,85&SignalGen_rx_data.c:22,222";
	/* <Root>/DAC2 Lookup Table */
	this.urlHashMap["SignalGen_rx:144"] = "SignalGen_rx.c:136,139,150,153&SignalGen_rx.h:74,86&SignalGen_rx_data.c:72,223";
	/* <Root>/DAC3 Lookup Table
 */
	this.urlHashMap["SignalGen_rx:148"] = "SignalGen_rx.c:181,184,206,209&SignalGen_rx.h:77,87&SignalGen_rx_data.c:123,224";
	/* <Root>/DAC4 Lookup Table */
	this.urlHashMap["SignalGen_rx:149"] = "SignalGen_rx.c:236,239,250,253&SignalGen_rx.h:80,88&SignalGen_rx_data.c:172,225";
	/* <Root>/Gain1 */
	this.urlHashMap["SignalGen_rx:214"] = "SignalGen_rx.c:107";
	/* <Root>/Gain2 */
	this.urlHashMap["SignalGen_rx:215"] = "SignalGen_rx.c:151";
	/* <Root>/Gain3 */
	this.urlHashMap["SignalGen_rx:216"] = "SignalGen_rx.c:207";
	/* <Root>/Gain4 */
	this.urlHashMap["SignalGen_rx:217"] = "SignalGen_rx.c:251";
	/* <Root>/Sum */
	this.urlHashMap["SignalGen_rx:220"] = "SignalGen_rx.c:104,123";
	/* <Root>/Sum1 */
	this.urlHashMap["SignalGen_rx:222"] = "SignalGen_rx.c:148,167";
	/* <Root>/Sum2 */
	this.urlHashMap["SignalGen_rx:223"] = "SignalGen_rx.c:204,223";
	/* <Root>/Sum3 */
	this.urlHashMap["SignalGen_rx:224"] = "SignalGen_rx.c:248,267";
	/* <Root>/ePWM7
DAC1 and DAC2 */
	this.urlHashMap["SignalGen_rx:27"] = "SignalGen_rx.c:169,429";
	/* <Root>/ePWM8
DAC3 and DAC4 */
	this.urlHashMap["SignalGen_rx:146"] = "SignalGen_rx.c:269,604";
	/* <S1>/Constant */
	this.urlHashMap["SignalGen_rx:232"] = "SignalGen_rx.c:94,126,194,226&SignalGen_rx.h:94&SignalGen_rx_data.c:231";
	/* <S1>/Gain */
	this.urlHashMap["SignalGen_rx:219"] = "SignalGen_rx.c:367&SignalGen_rx.h:59,106&SignalGen_rx_data.c:243";
	/* <S1>/Rate Transition3 */
	this.urlHashMap["SignalGen_rx:218"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:218";
	/* <S1>/SCI Receive */
	this.urlHashMap["SignalGen_rx:204"] = "SignalGen_rx.c:311,419&SignalGen_rx.h:60";
	/* <S1>/Switch1 */
	this.urlHashMap["SignalGen_rx:233"] = "SignalGen_rx.c:125,134";
	/* <S1>/Switch2 */
	this.urlHashMap["SignalGen_rx:231"] = "SignalGen_rx.c:93,102";
	/* <S1>/Switch3 */
	this.urlHashMap["SignalGen_rx:234"] = "SignalGen_rx.c:193,202";
	/* <S1>/Switch4 */
	this.urlHashMap["SignalGen_rx:235"] = "SignalGen_rx.c:225,234";
	/* <S2>/Data Type
Propagation */
	this.urlHashMap["SignalGen_rx:137:1"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:137:1";
	/* <S2>/Output */
	this.urlHashMap["SignalGen_rx:137:4"] = "SignalGen_rx.c:82,137,182,237,283,290,295,779&SignalGen_rx.h:65,100&SignalGen_rx_data.c:237";
	/* <S3>/DAC1 Vrms */
	this.urlHashMap["SignalGen_rx:241"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:241";
	/* <S3>/DAC2 Vrms */
	this.urlHashMap["SignalGen_rx:242"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:242";
	/* <S3>/DAC3 Vrms */
	this.urlHashMap["SignalGen_rx:243"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:243";
	/* <S3>/DAC4 Vrms */
	this.urlHashMap["SignalGen_rx:244"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:244";
	/* <S3>/Osciloscoppe view */
	this.urlHashMap["SignalGen_rx:246"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:246";
	/* <S3>/RMS */
	this.urlHashMap["SignalGen_rx:247"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:247";
	/* <S3>/RMS1 */
	this.urlHashMap["SignalGen_rx:248"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:248";
	/* <S3>/RMS2 */
	this.urlHashMap["SignalGen_rx:249"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:249";
	/* <S3>/RMS3 */
	this.urlHashMap["SignalGen_rx:250"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:250";
	/* <S4>/FixPt
Constant */
	this.urlHashMap["SignalGen_rx:137:3:2"] = "SignalGen_rx.c:282&SignalGen_rx.h:103&SignalGen_rx_data.c:240";
	/* <S4>/FixPt
Data Type
Duplicate */
	this.urlHashMap["SignalGen_rx:137:3:3"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:137:3:3";
	/* <S4>/FixPt
Sum1 */
	this.urlHashMap["SignalGen_rx:137:3:4"] = "SignalGen_rx.c:281";
	/* <S5>/Constant */
	this.urlHashMap["SignalGen_rx:137:5:4"] = "SignalGen_rx.c:291&SignalGen_rx.h:97&SignalGen_rx_data.c:234";
	/* <S5>/FixPt
Data Type
Duplicate1 */
	this.urlHashMap["SignalGen_rx:137:5:2"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:137:5:2";
	/* <S5>/FixPt
Switch */
	this.urlHashMap["SignalGen_rx:137:5:3"] = "SignalGen_rx.c:288,299&SignalGen_rx.h:91&SignalGen_rx_data.c:228";
	/* <S6>/Bias
offset */
	this.urlHashMap["SignalGen_rx:256"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:256";
	/* <S6>/Gain
to volts */
	this.urlHashMap["SignalGen_rx:257"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:257";
	/* <S7>/Rate Transition */
	this.urlHashMap["SignalGen_rx:262"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:262";
	/* <S7>/To Workspace */
	this.urlHashMap["SignalGen_rx:263"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:263";
	/* <S7>/ZOH
ADC simulation */
	this.urlHashMap["SignalGen_rx:264"] = "msg=rtwMsg_reducedBlock&block=SignalGen_rx:264";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "SignalGen_rx"};
	this.sidHashMap["SignalGen_rx"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "SignalGen_rx:225"};
	this.sidHashMap["SignalGen_rx:225"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "SignalGen_rx:137"};
	this.sidHashMap["SignalGen_rx:137"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "SignalGen_rx:236"};
	this.sidHashMap["SignalGen_rx:236"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "SignalGen_rx:137:3"};
	this.sidHashMap["SignalGen_rx:137:3"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<S5>"] = {sid: "SignalGen_rx:137:5"};
	this.sidHashMap["SignalGen_rx:137:5"] = {rtwname: "<S5>"};
	this.rtwnameHashMap["<S6>"] = {sid: "SignalGen_rx:251"};
	this.sidHashMap["SignalGen_rx:251"] = {rtwname: "<S6>"};
	this.rtwnameHashMap["<S7>"] = {sid: "SignalGen_rx:260"};
	this.sidHashMap["SignalGen_rx:260"] = {rtwname: "<S7>"};
	this.rtwnameHashMap["<Root>/Comunication"] = {sid: "SignalGen_rx:225"};
	this.sidHashMap["SignalGen_rx:225"] = {rtwname: "<Root>/Comunication"};
	this.rtwnameHashMap["<Root>/Constant"] = {sid: "SignalGen_rx:221"};
	this.sidHashMap["SignalGen_rx:221"] = {rtwname: "<Root>/Constant"};
	this.rtwnameHashMap["<Root>/Counter Limited"] = {sid: "SignalGen_rx:137"};
	this.sidHashMap["SignalGen_rx:137"] = {rtwname: "<Root>/Counter Limited"};
	this.rtwnameHashMap["<Root>/DAC1 Lookup Table"] = {sid: "SignalGen_rx:139"};
	this.sidHashMap["SignalGen_rx:139"] = {rtwname: "<Root>/DAC1 Lookup Table"};
	this.rtwnameHashMap["<Root>/DAC2 Lookup Table"] = {sid: "SignalGen_rx:144"};
	this.sidHashMap["SignalGen_rx:144"] = {rtwname: "<Root>/DAC2 Lookup Table"};
	this.rtwnameHashMap["<Root>/DAC3 Lookup Table "] = {sid: "SignalGen_rx:148"};
	this.sidHashMap["SignalGen_rx:148"] = {rtwname: "<Root>/DAC3 Lookup Table "};
	this.rtwnameHashMap["<Root>/DAC4 Lookup Table"] = {sid: "SignalGen_rx:149"};
	this.sidHashMap["SignalGen_rx:149"] = {rtwname: "<Root>/DAC4 Lookup Table"};
	this.rtwnameHashMap["<Root>/Gain1"] = {sid: "SignalGen_rx:214"};
	this.sidHashMap["SignalGen_rx:214"] = {rtwname: "<Root>/Gain1"};
	this.rtwnameHashMap["<Root>/Gain2"] = {sid: "SignalGen_rx:215"};
	this.sidHashMap["SignalGen_rx:215"] = {rtwname: "<Root>/Gain2"};
	this.rtwnameHashMap["<Root>/Gain3"] = {sid: "SignalGen_rx:216"};
	this.sidHashMap["SignalGen_rx:216"] = {rtwname: "<Root>/Gain3"};
	this.rtwnameHashMap["<Root>/Gain4"] = {sid: "SignalGen_rx:217"};
	this.sidHashMap["SignalGen_rx:217"] = {rtwname: "<Root>/Gain4"};
	this.rtwnameHashMap["<Root>/Simulation view"] = {sid: "SignalGen_rx:236"};
	this.sidHashMap["SignalGen_rx:236"] = {rtwname: "<Root>/Simulation view"};
	this.rtwnameHashMap["<Root>/Sum"] = {sid: "SignalGen_rx:220"};
	this.sidHashMap["SignalGen_rx:220"] = {rtwname: "<Root>/Sum"};
	this.rtwnameHashMap["<Root>/Sum1"] = {sid: "SignalGen_rx:222"};
	this.sidHashMap["SignalGen_rx:222"] = {rtwname: "<Root>/Sum1"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "SignalGen_rx:223"};
	this.sidHashMap["SignalGen_rx:223"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<Root>/Sum3"] = {sid: "SignalGen_rx:224"};
	this.sidHashMap["SignalGen_rx:224"] = {rtwname: "<Root>/Sum3"};
	this.rtwnameHashMap["<Root>/ePWM7 DAC1 and DAC2"] = {sid: "SignalGen_rx:27"};
	this.sidHashMap["SignalGen_rx:27"] = {rtwname: "<Root>/ePWM7 DAC1 and DAC2"};
	this.rtwnameHashMap["<Root>/ePWM8 DAC3 and DAC4"] = {sid: "SignalGen_rx:146"};
	this.sidHashMap["SignalGen_rx:146"] = {rtwname: "<Root>/ePWM8 DAC3 and DAC4"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "SignalGen_rx:232"};
	this.sidHashMap["SignalGen_rx:232"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/Demux"] = {sid: "SignalGen_rx:230"};
	this.sidHashMap["SignalGen_rx:230"] = {rtwname: "<S1>/Demux"};
	this.rtwnameHashMap["<S1>/Gain"] = {sid: "SignalGen_rx:219"};
	this.sidHashMap["SignalGen_rx:219"] = {rtwname: "<S1>/Gain"};
	this.rtwnameHashMap["<S1>/Rate Transition3"] = {sid: "SignalGen_rx:218"};
	this.sidHashMap["SignalGen_rx:218"] = {rtwname: "<S1>/Rate Transition3"};
	this.rtwnameHashMap["<S1>/SCI Receive"] = {sid: "SignalGen_rx:204"};
	this.sidHashMap["SignalGen_rx:204"] = {rtwname: "<S1>/SCI Receive"};
	this.rtwnameHashMap["<S1>/Switch1"] = {sid: "SignalGen_rx:233"};
	this.sidHashMap["SignalGen_rx:233"] = {rtwname: "<S1>/Switch1"};
	this.rtwnameHashMap["<S1>/Switch2"] = {sid: "SignalGen_rx:231"};
	this.sidHashMap["SignalGen_rx:231"] = {rtwname: "<S1>/Switch2"};
	this.rtwnameHashMap["<S1>/Switch3"] = {sid: "SignalGen_rx:234"};
	this.sidHashMap["SignalGen_rx:234"] = {rtwname: "<S1>/Switch3"};
	this.rtwnameHashMap["<S1>/Switch4"] = {sid: "SignalGen_rx:235"};
	this.sidHashMap["SignalGen_rx:235"] = {rtwname: "<S1>/Switch4"};
	this.rtwnameHashMap["<S1>/A1"] = {sid: "SignalGen_rx:226"};
	this.sidHashMap["SignalGen_rx:226"] = {rtwname: "<S1>/A1"};
	this.rtwnameHashMap["<S1>/A2"] = {sid: "SignalGen_rx:227"};
	this.sidHashMap["SignalGen_rx:227"] = {rtwname: "<S1>/A2"};
	this.rtwnameHashMap["<S1>/A3"] = {sid: "SignalGen_rx:228"};
	this.sidHashMap["SignalGen_rx:228"] = {rtwname: "<S1>/A3"};
	this.rtwnameHashMap["<S1>/A4"] = {sid: "SignalGen_rx:229"};
	this.sidHashMap["SignalGen_rx:229"] = {rtwname: "<S1>/A4"};
	this.rtwnameHashMap["<S2>/Data Type Propagation"] = {sid: "SignalGen_rx:137:1"};
	this.sidHashMap["SignalGen_rx:137:1"] = {rtwname: "<S2>/Data Type Propagation"};
	this.rtwnameHashMap["<S2>/Force to be scalar"] = {sid: "SignalGen_rx:137:2"};
	this.sidHashMap["SignalGen_rx:137:2"] = {rtwname: "<S2>/Force to be scalar"};
	this.rtwnameHashMap["<S2>/Increment Real World"] = {sid: "SignalGen_rx:137:3"};
	this.sidHashMap["SignalGen_rx:137:3"] = {rtwname: "<S2>/Increment Real World"};
	this.rtwnameHashMap["<S2>/Output"] = {sid: "SignalGen_rx:137:4"};
	this.sidHashMap["SignalGen_rx:137:4"] = {rtwname: "<S2>/Output"};
	this.rtwnameHashMap["<S2>/Wrap To Zero"] = {sid: "SignalGen_rx:137:5"};
	this.sidHashMap["SignalGen_rx:137:5"] = {rtwname: "<S2>/Wrap To Zero"};
	this.rtwnameHashMap["<S2>/y"] = {sid: "SignalGen_rx:137:6"};
	this.sidHashMap["SignalGen_rx:137:6"] = {rtwname: "<S2>/y"};
	this.rtwnameHashMap["<S3>/DAC1"] = {sid: "SignalGen_rx:237"};
	this.sidHashMap["SignalGen_rx:237"] = {rtwname: "<S3>/DAC1"};
	this.rtwnameHashMap["<S3>/DAC2"] = {sid: "SignalGen_rx:238"};
	this.sidHashMap["SignalGen_rx:238"] = {rtwname: "<S3>/DAC2"};
	this.rtwnameHashMap["<S3>/DAC3"] = {sid: "SignalGen_rx:239"};
	this.sidHashMap["SignalGen_rx:239"] = {rtwname: "<S3>/DAC3"};
	this.rtwnameHashMap["<S3>/DAC4"] = {sid: "SignalGen_rx:240"};
	this.sidHashMap["SignalGen_rx:240"] = {rtwname: "<S3>/DAC4"};
	this.rtwnameHashMap["<S3>/DAC1 Vrms"] = {sid: "SignalGen_rx:241"};
	this.sidHashMap["SignalGen_rx:241"] = {rtwname: "<S3>/DAC1 Vrms"};
	this.rtwnameHashMap["<S3>/DAC2 Vrms"] = {sid: "SignalGen_rx:242"};
	this.sidHashMap["SignalGen_rx:242"] = {rtwname: "<S3>/DAC2 Vrms"};
	this.rtwnameHashMap["<S3>/DAC3 Vrms"] = {sid: "SignalGen_rx:243"};
	this.sidHashMap["SignalGen_rx:243"] = {rtwname: "<S3>/DAC3 Vrms"};
	this.rtwnameHashMap["<S3>/DAC4 Vrms"] = {sid: "SignalGen_rx:244"};
	this.sidHashMap["SignalGen_rx:244"] = {rtwname: "<S3>/DAC4 Vrms"};
	this.rtwnameHashMap["<S3>/Demux"] = {sid: "SignalGen_rx:245"};
	this.sidHashMap["SignalGen_rx:245"] = {rtwname: "<S3>/Demux"};
	this.rtwnameHashMap["<S3>/Osciloscoppe view"] = {sid: "SignalGen_rx:246"};
	this.sidHashMap["SignalGen_rx:246"] = {rtwname: "<S3>/Osciloscoppe view"};
	this.rtwnameHashMap["<S3>/RMS"] = {sid: "SignalGen_rx:247"};
	this.sidHashMap["SignalGen_rx:247"] = {rtwname: "<S3>/RMS"};
	this.rtwnameHashMap["<S3>/RMS1"] = {sid: "SignalGen_rx:248"};
	this.sidHashMap["SignalGen_rx:248"] = {rtwname: "<S3>/RMS1"};
	this.rtwnameHashMap["<S3>/RMS2"] = {sid: "SignalGen_rx:249"};
	this.sidHashMap["SignalGen_rx:249"] = {rtwname: "<S3>/RMS2"};
	this.rtwnameHashMap["<S3>/RMS3"] = {sid: "SignalGen_rx:250"};
	this.sidHashMap["SignalGen_rx:250"] = {rtwname: "<S3>/RMS3"};
	this.rtwnameHashMap["<S3>/Scale to 3.3 Volts"] = {sid: "SignalGen_rx:251"};
	this.sidHashMap["SignalGen_rx:251"] = {rtwname: "<S3>/Scale to 3.3 Volts"};
	this.rtwnameHashMap["<S3>/Subsystem"] = {sid: "SignalGen_rx:260"};
	this.sidHashMap["SignalGen_rx:260"] = {rtwname: "<S3>/Subsystem"};
	this.rtwnameHashMap["<S4>/u"] = {sid: "SignalGen_rx:137:3:1"};
	this.sidHashMap["SignalGen_rx:137:3:1"] = {rtwname: "<S4>/u"};
	this.rtwnameHashMap["<S4>/FixPt Constant"] = {sid: "SignalGen_rx:137:3:2"};
	this.sidHashMap["SignalGen_rx:137:3:2"] = {rtwname: "<S4>/FixPt Constant"};
	this.rtwnameHashMap["<S4>/FixPt Data Type Duplicate"] = {sid: "SignalGen_rx:137:3:3"};
	this.sidHashMap["SignalGen_rx:137:3:3"] = {rtwname: "<S4>/FixPt Data Type Duplicate"};
	this.rtwnameHashMap["<S4>/FixPt Sum1"] = {sid: "SignalGen_rx:137:3:4"};
	this.sidHashMap["SignalGen_rx:137:3:4"] = {rtwname: "<S4>/FixPt Sum1"};
	this.rtwnameHashMap["<S4>/y"] = {sid: "SignalGen_rx:137:3:5"};
	this.sidHashMap["SignalGen_rx:137:3:5"] = {rtwname: "<S4>/y"};
	this.rtwnameHashMap["<S5>/U"] = {sid: "SignalGen_rx:137:5:1"};
	this.sidHashMap["SignalGen_rx:137:5:1"] = {rtwname: "<S5>/U"};
	this.rtwnameHashMap["<S5>/Constant"] = {sid: "SignalGen_rx:137:5:4"};
	this.sidHashMap["SignalGen_rx:137:5:4"] = {rtwname: "<S5>/Constant"};
	this.rtwnameHashMap["<S5>/FixPt Data Type Duplicate1"] = {sid: "SignalGen_rx:137:5:2"};
	this.sidHashMap["SignalGen_rx:137:5:2"] = {rtwname: "<S5>/FixPt Data Type Duplicate1"};
	this.rtwnameHashMap["<S5>/FixPt Switch"] = {sid: "SignalGen_rx:137:5:3"};
	this.sidHashMap["SignalGen_rx:137:5:3"] = {rtwname: "<S5>/FixPt Switch"};
	this.rtwnameHashMap["<S5>/Y"] = {sid: "SignalGen_rx:137:5:5"};
	this.sidHashMap["SignalGen_rx:137:5:5"] = {rtwname: "<S5>/Y"};
	this.rtwnameHashMap["<S6>/In1"] = {sid: "SignalGen_rx:252"};
	this.sidHashMap["SignalGen_rx:252"] = {rtwname: "<S6>/In1"};
	this.rtwnameHashMap["<S6>/In2"] = {sid: "SignalGen_rx:253"};
	this.sidHashMap["SignalGen_rx:253"] = {rtwname: "<S6>/In2"};
	this.rtwnameHashMap["<S6>/In3"] = {sid: "SignalGen_rx:254"};
	this.sidHashMap["SignalGen_rx:254"] = {rtwname: "<S6>/In3"};
	this.rtwnameHashMap["<S6>/In4"] = {sid: "SignalGen_rx:255"};
	this.sidHashMap["SignalGen_rx:255"] = {rtwname: "<S6>/In4"};
	this.rtwnameHashMap["<S6>/Bias offset"] = {sid: "SignalGen_rx:256"};
	this.sidHashMap["SignalGen_rx:256"] = {rtwname: "<S6>/Bias offset"};
	this.rtwnameHashMap["<S6>/Gain to volts"] = {sid: "SignalGen_rx:257"};
	this.sidHashMap["SignalGen_rx:257"] = {rtwname: "<S6>/Gain to volts"};
	this.rtwnameHashMap["<S6>/Mux"] = {sid: "SignalGen_rx:258"};
	this.sidHashMap["SignalGen_rx:258"] = {rtwname: "<S6>/Mux"};
	this.rtwnameHashMap["<S6>/Out1"] = {sid: "SignalGen_rx:259"};
	this.sidHashMap["SignalGen_rx:259"] = {rtwname: "<S6>/Out1"};
	this.rtwnameHashMap["<S7>/ADC"] = {sid: "SignalGen_rx:261"};
	this.sidHashMap["SignalGen_rx:261"] = {rtwname: "<S7>/ADC"};
	this.rtwnameHashMap["<S7>/Rate Transition"] = {sid: "SignalGen_rx:262"};
	this.sidHashMap["SignalGen_rx:262"] = {rtwname: "<S7>/Rate Transition"};
	this.rtwnameHashMap["<S7>/To Workspace"] = {sid: "SignalGen_rx:263"};
	this.sidHashMap["SignalGen_rx:263"] = {rtwname: "<S7>/To Workspace"};
	this.rtwnameHashMap["<S7>/ZOH ADC simulation"] = {sid: "SignalGen_rx:264"};
	this.sidHashMap["SignalGen_rx:264"] = {rtwname: "<S7>/ZOH ADC simulation"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
