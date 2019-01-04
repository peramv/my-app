var requestURL = null;


function loadHistoricalScreen ()
{
	auditRecid = _vrecid[currentSelectedRow];
	/*
	requestURL = buildBaseURL("PaymentSearch_Historical");	
	requestURL = appendParam(requestURL, "auditRecid", _vrecid[currentSelectedRow]);
	window.open(requestURL);
	*/
}

function sendHistoricalCall(startRecord, numberOfRecords)
{
	requestURL = buildBaseURL("PaymentSearch_HistoricalList");
	requestURL = appendParam(requestURL, "auditType", "PayRecon");
	requestURL = appendParam(requestURL, "auditRecid", document.getElementById("vrecid").value);
	requestURL = appendParam(requestURL, "startRecNum", startRecord);
	requestURL = appendParam(requestURL, "requestRecNum", numberOfRecords);
	
	callJobAndEval(requestURL);
}
