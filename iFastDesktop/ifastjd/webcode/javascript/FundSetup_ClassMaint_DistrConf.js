//******************************************************
function loading()
{	
	if ( UTL.getElem( "ClassData" ) )
	{			
		ClassDataManager.init( XML.parseToXML( UTL.getElem( "ClassData" ).xml ) );
	}
	
	if ( UTL.getElem( "UpdatedClassData" ) )
	{		
		ClassDataManager.loadExistingUpdates( XML.parseToXML(  UTL.getElem( "UpdatedClassData" ).xml ) );
	}
		
	ClassDataManager.initScreen( "DistributionConfig", "DistrConf" );	
	initIncomeDistribution();
	initCapitalGains();
}

//******************************************************
function initIncomeDistribution()
{	
	if ( _isAddMode )
	{
		if ( UTL.getElem( "DistributionConfig/id" ).value == "" )
		{
			
			UTL.getElem( "DistributionConfig/id" ).value = "no";
		}
		
		if ( UTL.getElem( "DistributionConfig/id" ).value == "yes" )
		{
			UTL.getElem( "idApplicableFld" ).checked = true;
			enableIDFields();
		}
		else
		{
			UTL.getElem( "idApplicableFld" ).checked = false;
			disableIDFields();
		}	
	}		
		
	if ( UTL.getElem( "DistributionConfig/id" ).value == 'yes' )
	{		
		if ( UTL.getElem( "DistributionConfig/idDefInvestOpt" ).value == "CS" )
		{
			UTL.getElem( "cs_idDefInvestOptFld" ).checked = true;
		}
		else
		{
			UTL.getElem( "ri_idDefInvestOptFld" ).checked = true;
		}
		
		if ( UTL.getElem( "DistributionConfig/idOverrideOpt" ).value.indexOf( "CS" ) != -1 )
		{
			UTL.getElem( "cs_idOverrideOptFld" ).checked = true;
		}
		if ( UTL.getElem( "DistributionConfig/idOverrideOpt" ).value.indexOf( "RD" ) != -1 )
		{
			UTL.getElem( "rd_idOverrideOptFld" ).checked = true;
		}
		if ( UTL.getElem( "DistributionConfig/idOverrideOpt" ).value.indexOf( "RI" ) != -1 )
		{
			UTL.getElem( "ri_idOverrideOptFld" ).checked = true;
		}
	}	
}

//******************************************************
function clickHandler_idDefaultInvestRadio( radio )
{		
	UTL.getElem( "DistributionConfig/idDefInvestOpt" ).value = radio.value;
	UTL.getElem( "DistributionConfig/idDefInvestDesc" ).value = radio.desc;
	
	ClassDataManager.setScreenUpdated();
}

//******************************************************
function clickHandler_idOverrideCheckbox()
{	
	updateIdOverrideFld();
	ClassDataManager.setScreenUpdated();
}

//******************************************************
function updateIdOverrideFld()
{
	var valArray = [];
	if ( UTL.getElem( "cs_idOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "cs_idOverrideOptFld" ).value;
	}	
	if ( UTL.getElem( "ri_idOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "ri_idOverrideOptFld" ).value;
	}
	if ( UTL.getElem( "rd_idOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "rd_idOverrideOptFld" ).value;
	}
	
	UTL.getElem( "DistributionConfig/idOverrideOpt" ).value = valArray.toString();
}

//******************************************************
function clickHandler_idApplicableFld( checkbox )
{
	if ( checkbox.checked )
	{		
		UTL.getElem( "DistributionConfig/id" ).value = 'yes';
		UTL.getElem( "DistributionConfig/idDesc" ).value = "Income Distribution";
		UTL.getElem( "cs_idDefInvestOptFld" ).checked = true;
		clickHandler_idDefaultInvestRadio( UTL.getElem( "cs_idDefInvestOptFld" ) );
		enableIDFields();		
		
	}
	else
	{
		UTL.getElem( "DistributionConfig/id" ).value = 'no';
		UTL.getElem( "DistributionConfig/idDesc" ).value = "";		
		disableIDFields();
		clearIDFields();
	}
}

//******************************************************
function enableIDFields()
{
	UTL.getElem( "cs_idDefInvestOptFld" ).disabled = false;
	UTL.getElem( "ri_idDefInvestOptFld" ).disabled = false;
	UTL.getElem( "cs_idOverrideOptFld" ).disabled = false;
	UTL.getElem( "rd_idOverrideOptFld" ).disabled = false;
	UTL.getElem( "ri_idOverrideOptFld" ).disabled = false;
}

//******************************************************
function disableIDFields()
{
	UTL.getElem( "cs_idDefInvestOptFld" ).disabled = true;
	UTL.getElem( "ri_idDefInvestOptFld" ).disabled = true;
	UTL.getElem( "cs_idOverrideOptFld" ).disabled = true;
	UTL.getElem( "rd_idOverrideOptFld" ).disabled = true;
	UTL.getElem( "ri_idOverrideOptFld" ).disabled = true;
}

//******************************************************
function clearIDFields()
{
	UTL.getElem( "cs_idDefInvestOptFld" ).checked = false;	
	UTL.getElem( "ri_idDefInvestOptFld" ).checked = false;
	UTL.getElem( "DistributionConfig/idDefInvestOpt" ).value = "";
	UTL.getElem( "DistributionConfig/idDefInvestDesc" ).value = "";
	
	UTL.getElem( "cs_idOverrideOptFld" ).checked = false;
	UTL.getElem( "rd_idOverrideOptFld" ).checked = false;
	UTL.getElem( "ri_idOverrideOptFld" ).checked = false;
	updateIdOverrideFld();
	ClassDataManager.setScreenUpdated();
}			

//******************************************************
function initCapitalGains()
{	
	if ( _isAddMode )
	{
		if ( UTL.getElem( "DistributionConfig/cd" ).value == "" )
		{			
			UTL.getElem( "DistributionConfig/cd" ).value = "no";
		}
		
		if ( UTL.getElem( "DistributionConfig/cd" ).value == "yes" )
		{
			UTL.getElem( "cdApplicableFld" ).checked = true;
			enableCDFields();
		}
		else
		{
			UTL.getElem( "cdApplicableFld" ).checked = false;
			disableCDFields();
		}	
	} 
	
	if ( UTL.getElem( "DistributionConfig/cd" ).value == 'yes' )
	{	
		if ( UTL.getElem( "DistributionConfig/cdDefInvestOpt" ).value == "CS" )
		{
			UTL.getElem( "cs_cdDefInvestOptFld" ).checked = true;
		}
		else
		{
			UTL.getElem( "ri_cdDefInvestOptFld" ).checked = true;
		}
		
		if ( UTL.getElem( "DistributionConfig/cdOverrideOpt" ).value.indexOf( "CS" ) != -1 )
		{
			UTL.getElem( "cs_cdOverrideOptFld" ).checked = true;
		}
		if ( UTL.getElem( "DistributionConfig/cdOverrideOpt" ).value.indexOf( "RD" ) != -1 )
		{
			UTL.getElem( "rd_cdOverrideOptFld" ).checked = true;
		}
		if ( UTL.getElem( "DistributionConfig/cdOverrideOpt" ).value.indexOf( "RI" ) != -1 )
		{
			UTL.getElem( "ri_cdOverrideOptFld" ).checked = true;
		}
	}
}

//******************************************************
function clickHandler_cdDefaultInvestRadio( radio )
{	
	UTL.getElem( "DistributionConfig/cdDefInvestOpt" ).value = radio.value;
	UTL.getElem( "DistributionConfig/cdDefInvestDesc" ).value = radio.desc;
	
	ClassDataManager.setScreenUpdated();
}

//******************************************************
function clickHandler_cdOverrideCheckbox()
{	
	updateCdOverrideFld();
	ClassDataManager.setScreenUpdated();
}

//******************************************************
function updateCdOverrideFld()
{
	var valArray = [];
	if ( UTL.getElem( "cs_cdOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "cs_cdOverrideOptFld" ).value;
	}	
	if ( UTL.getElem( "ri_cdOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "ri_cdOverrideOptFld" ).value;
	}
	if ( UTL.getElem( "rd_cdOverrideOptFld" ).checked )
	{
		valArray[valArray.length] = UTL.getElem( "rd_cdOverrideOptFld" ).value;
	}
	
	UTL.getElem( "DistributionConfig/cdOverrideOpt" ).value = valArray.toString();
}

//******************************************************
function clickHandler_cdApplicableFld( checkbox )
{
	if ( checkbox.checked )
	{
		UTL.getElem( "DistributionConfig/cd" ).value = 'yes';
		UTL.getElem( "DistributionConfig/cdDesc" ).value = "Capital Gains";
		enableCDFields();
		UTL.getElem( "cs_cdDefInvestOptFld" ).checked = true;
	}
	else
	{
		UTL.getElem( "DistributionConfig/cd" ).value = 'no';
		UTL.getElem( "DistributionConfig/cdDesc" ).value = "";
		disableCDFields();
		clearCDFields();
	}
}

//******************************************************
function enableCDFields()
{
	UTL.getElem( "cs_cdDefInvestOptFld" ).disabled = false;
	UTL.getElem( "ri_cdDefInvestOptFld" ).disabled = false;
	UTL.getElem( "cs_cdOverrideOptFld" ).disabled = false;
	UTL.getElem( "rd_cdOverrideOptFld" ).disabled = false;
	UTL.getElem( "ri_cdOverrideOptFld" ).disabled = false;
}

//******************************************************
function disableCDFields()
{
	UTL.getElem( "cs_cdDefInvestOptFld" ).disabled = true;
	UTL.getElem( "ri_cdDefInvestOptFld" ).disabled = true;
	UTL.getElem( "cs_cdOverrideOptFld" ).disabled = true;
	UTL.getElem( "rd_cdOverrideOptFld" ).disabled = true;
	UTL.getElem( "ri_cdOverrideOptFld" ).disabled = true;
}

//******************************************************
function clearCDFields()
{
	UTL.getElem( "cs_cdDefInvestOptFld" ).checked = false;
	UTL.getElem( "ri_cdDefInvestOptFld" ).checked = false;
	UTL.getElem( "cs_cdOverrideOptFld" ).checked = false;
	UTL.getElem( "rd_cdOverrideOptFld" ).checked = false;
	UTL.getElem( "ri_cdOverrideOptFld" ).checked = false;
}					

//******************************************************
function clickHandler_resetScreenBtn()
{
	if ( confirmReset() )
	{
		ClassDataManager.resetScreen();
		initIncomeDistribution();
		initCapitalGains();
	}
}
