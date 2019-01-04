/*********************************************************************************************
 * @file    RESPGrantInfo2.Controller.js
 * @author    Rod Walker
 * @desc    Controller JS file for RESP Grant Information screen.
 *
 * History:
 *  16 Jul 2014 Aurkarn Mongkonrat P0241773 T81086
 *                    - Redesign the whole screen to be more flexible for the new grants.
 *
 *  21 Jul 2014 Aurkarn Mongkonrat P0241773 T81123
 *                    - Fix issues from T81086 and issue log
 *
 *  08 Sep 2014 Aurkarn Mongkonrat P0241773 T81293
 *                    - Disable grant status for SAGES
 *
 *	07 Sep 2015 Peeranut L. P0241773 T81342
 *					  - Fixed translation to avoid hard code.
 *
 *  20 Oct 2015 Aurkarn Mongkonrat P0241773 T81559 DFT0054910
 *					  - Add effective date validation for SAGES and ADDCESG.
 * 
 *  21 Oct 2015 Aurkarn Mongkonrat P0241773 T81559 DFT0055013 
 *					  - Fix User is able to add same grant request multiple times
 *
 *  21 Oct 2015 Aurkarn Mongkonrat P0241773 T81559 DFT0054856 
 *					  - Setting of ADDCESG StopDate should be based on update flag.
 *
 *  02 Nov 2015 Aurkarn Mongkonrat P0241773 T81642 DFT0055520 
 *					  - Fix javascript error when requesting BCTESG grant.
 *
 *  12 Nov 2015 Aurkarn Mongkonrat P0241773 T81721 DFT0056272 
 *					  - Change to set default effective date from value sent by back-end.
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
 *
 *  03 Dec 2015 Aurkarn Mongkonrat P0241773 T81814 DFT0057065 
 *					  - Update db-audit key
 *
 *  22 Dec 2015 Nopphawan Hatthaseriphong P0250179 T81941
 *					  - Ability to delete RESP grant request information
 *
 *  28 Dec 2015 Aurkarn Mongkonrat P0241773 T81957 DFT0057748 DFT0057843
 *					  - Enable stopdate field for all grant types and implement its validations.
 *
 *  15 Jan 2016 Nopphawan Hatthaseriphong P0250179 T82031 DFT0058464
 *					  - Not allow user to modify a grant that is pending status.
 *
 *  21 Jan 2016 Nopphawan Hatthaseriphong P0250179 T82057 DFT0058662 DFT0058748
 *					  - Add function to get GrantTypeOption list for add mode.
 *                    - Fix grant status inside grid not translated.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					  - Fixed screens don't response when user's profile has too many slots attached. 
 *
 *	13 May 2016 Aurkarn M. P0241773 DFT0062785 T82820
 *					  - Fix issue where BCTESG Grant Status reason not refreshed 
 *                      when status is changed.
 *                    - Fix issue where start and stop date of QESI is incorrect
 *                      when changing GrantYear
 *
 *  13 May 2016 Busarakorn S. P0241773 DFT0059608 DFT0059695 DFT0060674 DFT0061701 T82829 
 *                    - Enable stopdate field for grant request type is 'Period' or 'OneTime'.
 *                    - Removed logic to override default stop for ADDCESG.
 *
 *  27 May 2016 Busarakorn S. P0241773 INC0029783 CHG0045600 INC0029000 CHG45602 T82937 R16.4 QV3
 *                    - Enable Stopdate Grant Year.
 *
 *  03 Jun 2016 Busarakorn S. P0241773 DFT0063552 T83012 R16.4
 *                    - Enable granttype for add SAGES.
 *
 *  31 Oct 2016 Nopphawan Hatthaseriphong P0241773 T84157 INC0031814
 *              - Update the effective date for ADCESG when RT511 is indicated
 *                (add new function selectRetroactiveChange).
 *                The effective date is sent from back-end as 'minStartDateRT511'.
 *  
 *  21 Nov 2016 Gomoot T. P0241773 T84157 INC0032235
 *              - When user modify Addition CESG (ADDCESG) grant Type from 
 *               Stop to Request status. The Stop date will be auto updated to
 *               defaultStopDate of ADDCESG grantType.
 *  
 *  17 Feb 2017 Narin Suanlamyai P0241773 T84889 DFT0072157
 *              - In Modify mode, when user modify the Retroactive ADCESG option from 
 *				  "Generated RT511" to blank, the Effective date will not be changed.
 *
 *
 *  23 Feb 2017 Narin Suanlamyai P0256094 T84842 DFT0070268
 *              - Fixed grant status with active/passive words.
 *                
 *********************************************************************************************/

DesktopWeb.ScreenController = function () {

    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();

    var _initView = "dtGrantInfoINQ"
    var _updateView = "dtGrantInfoUPD";
    var _validateView = "dtGrantInfoVAL";
    var _historicalView = "dtHistoricalInfo";
    var _initDataXML = null;
    var _currentBenefGrantInfoXML = null;
    var _latestUUID = 0;

    var _addPerm = null;
    var _modPerm = null;
    var _delPerm = null;

    var _GRANT_YEAR = 'GrantYear';
    var _GRANT_PERIOD = 'Period';
    var _GRANT_ONETIME = 'OneTime';
    var _GRANTTYPE_QESI = 'QESI';
    var _GRANTTYPE_ADDCESG = 'ADDCESG';
    var _GRANTTYPE_CESG = 'CESG';
    var _GRANTTYPE_SAGES = 'SAGES';
    var _GRANTTYPE_BCTESG = 'BCTESG';

    var _listGrantTypeOption_add = null;

    // PRIVATE METHODS ****************************************
    function populateScreen() {
        _addPerm = IFDS.Xml.getNodeValue(_initDataXML, '//Permission/addPerm').toLowerCase() == 'yes';
        _modPerm = IFDS.Xml.getNodeValue(_initDataXML, '//Permission/modPerm').toLowerCase() == 'yes';
        _delPerm = IFDS.Xml.getNodeValue(_initDataXML, '//Permission/delPerm').toLowerCase() == 'yes';
        _resources.fields['benefCMB'].loadData(IFDS.Xml.getNode(_initDataXML, '//List[@listName="BeneficiaryList"]'));

        if (DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID'].trim() !== "") { 
            _resources.fields['benefCMB'].setValue(DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
            _resources.fields['benefCMB'].disable();
        } else {
            _resources.fields['benefCMB'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '//DefaultValues/benefID'));
            _resources.fields['benefCMB'].enable();
        }

        populateBenefInfoAndGrantInfo();
    }


    function populateBeneficiaryInfo() {
        var benefNode = IFDS.Xml.getNode(_currentBenefGrantInfoXML, '//Beneficiary');
        var siblingOnly = IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/siblingOnly').toLowerCase();

        _resources.fields['sin'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/sin'));
        _resources.fields['dob'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(benefNode,
                                                                                                    'BenefInfo/dob')));
        _resources.fields['taxjuris'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/taxjuris'));
        _resources.fields['taxTypeDesc'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/taxTypeDesc'));
        _resources.fields['siblingOnly'].setValue((siblingOnly == 'y' ? _translationMap['Yes']:_translationMap['No']));
        _resources.fields['specimenNum'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/specimenNum'));
        _resources.fields['pcgName'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/pcgName'));
        _resources.fields['pcgSINBN'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenefInfo/pcgSINBN'));

        _resources.fields['beneAddr'].setValue(IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/addr1')
            + (IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/addr2') != "" ? ", " : "")
            + IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/addr2')
            + (IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/addr3') != "" ? ", " : "")
            + IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/addr3')
            + (IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/cntry') != "" ? ", " : "")
            + IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/cntry')
            + (IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/pstl') != "" ? ", " : "")
            + IFDS.Xml.getNodeValue(benefNode, 'BenAddrInfo/pstl'));
    }

    function populateGrantInfo() {
        _resources.grids['grants'].loadData(IFDS.Xml.getNode(_currentBenefGrantInfoXML, '//GrantList'));
        _listGrantTypeOption_add = getGrantTypeOptionAddList();

        if (_addPerm) {
            _resources.grids['grants'].enableButton('addBtn');
        } else {
            _resources.grids['grants'].disableButton('addBtn');
        }
    }

    function ReloadBenefInfoAndGrantInfo() {
        var viewParamXML = IFDS.Xml.newDocument("data");
        IFDS.Xml.addSingleNode(viewParamXML, 'runMode', 'reload');
        IFDS.Xml.addSingleNode(viewParamXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
        IFDS.Xml.addSingleNode(viewParamXML, 'benefID', _resources.fields['benefCMB'].getValue());

        DesktopWeb.Ajax.doSmartviewAjax(_initView,
                                        null,
                                        viewParamXML,
                                        responseHandler,
                                        _translationMap['ProcMsg_Loading']);

        function responseHandler(success, responseXML) {
            if (success) {
                _currentBenefGrantInfoXML = responseXML;
                populateBenefInfoAndGrantInfo();
            }
        }
    }

    function populateBenefInfoAndGrantInfo() {
        populateBeneficiaryInfo();
        populateGrantInfo();
        populateGrantTypeFilterDropdown();
    }

    function buildUpdateXML() {
        var grantRecords = _resources.grids['grants'].getStore().queryBy(function(record) {
                                                                           return record.get('runMode') == _self.ADD ||
                                                                                  record.get('runMode') == _self.MOD ||
                                                                           record.get('runMode') == _self.DEL;
                                                                        });

        if (grantRecords.length <= 0)
            return null;

        var updateXML = IFDS.Xml.newDocument("data");
        var grantListXML = IFDS.Xml.addSingleNode(updateXML, "GrantList");
        for (var i = 0; i < grantRecords.length; i++) {
            buildUpdateXMLByRecord(grantListXML, grantRecords.itemAt(i).data, grantRecords.itemAt(i).data.runMode);
        }

        return updateXML;
    }

    function buildUpdateXMLByRecord(xml, data, runMode) {
        var grantXML = IFDS.Xml.addSingleNode(xml, 'GrantDetail', '');

        IFDS.Xml.addAttribute(grantXML, 'RecordSource', data['grantInfoUUID']);
        IFDS.Xml.addSingleNode(grantXML, 'runMode', runMode);
        IFDS.Xml.addSingleNode(grantXML, 'grantInfoUUID', data['grantInfoUUID']);
        IFDS.Xml.addSingleNode(grantXML, 'grantType', data['grantType']);
        IFDS.Xml.addSingleNode(grantXML, 'grantStatus', data['grantStat']);
        IFDS.Xml.addSingleNode(grantXML, 'startDate', DesktopWeb.Util.getSMVDateValue(data['eligDate']));
        IFDS.Xml.addSingleNode(grantXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
        IFDS.Xml.addSingleNode(grantXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
        IFDS.Xml.addSingleNode(grantXML, 'benefID', _resources.fields['benefCMB'].getValue());

        if (getGrantRequestType(data['grantType']) === _GRANT_YEAR) {
            IFDS.Xml.addSingleNode(grantXML, 'grantYear', data['grantYear']);
        }

        if (data['grantType'] == _GRANTTYPE_ADDCESG) {
            IFDS.Xml.addSingleNode(grantXML, 'retroactive', data['retroactive']);
        }

        if (data['grantType'] == _GRANTTYPE_QESI) {
            IFDS.Xml.addSingleNode(grantXML, 'stopReason', data['stopReason']);
        }
        
        IFDS.Xml.addSingleNode(grantXML, 'rejReason', data['rejReason']);
    	IFDS.Xml.addSingleNode(grantXML, 'version', data['version']);
    	IFDS.Xml.addSingleNode(grantXML, 'delPerm', data['delPerm']);
    }

    function populateGrantTypeFilterDropdown() { 
        var grantTypeArray = [["All", _translationMap['All']]];
        var alreadyAdded = [];
		
        _resources.grids['grants'].getStore().clearFilter();
        
        for (var i = 0; i < _resources.grids['grants'].getStore().getCount(); i++) {
            var grantType = _resources.grids['grants'].getStore().getAt(i).data.grantType;
            var grantTypeDesc = _resources.grids['grants'].getStore().getAt(i).data.grantTypeDesc;
            
            if (alreadyAdded.indexOf(grantType) < 0) {
                var grantItem = [grantType, grantTypeDesc];
                alreadyAdded.push(grantType);
                grantTypeArray.push(grantItem);
            }
        }

        _resources.fields['grantTypeCMB'].loadData(grantTypeArray);
        _resources.fields['grantTypeCMB'].setValue("All");
    }

    function getDisplay(listName, code) {
        var listNode = IFDS.Xml.getNode(_initDataXML,
                                        '//List[@listName = "' + listName + '"]/Element[code="' + code + '"]');

        return (listNode) ? IFDS.Xml.getNodeValue(listNode, 'value'):code;
    }

    function validateGrant(data, action) {
        // build parameter xml
        var dataXML = IFDS.Xml.newDocument('data');

        buildUpdateXMLByRecord(dataXML, data, action);
        DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, dataXML, responseHandler, _translationMap['Validating']);

        function responseHandler(success, responseXML, contextErrors, contextWarnings) {
            if (success) {
                _self.updatesFlag = true;
                updateGrantRecord(data, action);
                _resources.popups['grantMaint'].hide();
            }
        }
    }

    function updateGrantRecord(data, action) {
        if (action == _self.ADD && !data['isModifyingNewRec']) {
            _resources.grids['grants'].addRecord(data);
            _resources.grids['grants'].selectLastRecord();

            populateGrantTypeFilterDropdown();
        } else if (action == _self.MOD ||
        	      (action == _self.ADD && data['isModifyingNewRec']) ||
                  (action == _self.DEL && !data['isModifyingNewRec'])) {
        	
            var grantRec = _resources.grids['grants'].getSelectedRecord();

            // Update grid
            grantRec.data['runMode'] = data['runMode'];
            grantRec.data['errMsg'] = '';
            grantRec.data['grantStat'] = data['grantStat'];
            grantRec.data['eligDate'] = data['eligDate'];
            grantRec.data['stopDate'] = data['stopDate'];
            grantRec.data['grantYear'] = data['grantYear'];
            grantRec.data['retroactive'] = data['retroactive'];
            grantRec.data['stopReason'] = data['stopReason'];
            grantRec.data['rejReason'] = data['rejReason']

            grantRec.commit();
        }
    }

    function getGrantRequestType(grantType) {
        return IFDS.Xml.getNodeValue(
                 _currentBenefGrantInfoXML,
                 '//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + grantType + '"]/grantRequestType');
    }

    function effectiveDateChange(isUpdateRelatedFields) {
        var grantPopup = _resources.popups['grantMaint'];
        var grantType = grantPopup.getField('grantType').getValue();
        var year = '';
        var retroactiveValue = '';
        
        if (grantPopup.getField('effectiveDate').getValue() != '') {
            year = grantPopup.getField('effectiveDate').getValue().getYear();
        }
        
        if (isUpdateRelatedFields) {
        	if (getGrantRequestType(grantType) === _GRANT_YEAR) {
        		grantPopup.getField('year').setValue(year);
        	}
            
        }
    }

    function selectGrantStatusChange(grantType, grantStatus) {
        var grantPopup = _resources.popups['grantMaint'];

		grantPopup.getField('stopReason').setValue('');
		grantPopup.rejReason = '0';
        if (grantType == _GRANTTYPE_QESI && grantStatus == 'Stopped') {
            grantPopup.getField('stopReason').show();
            grantPopup.getField('stopReason').enableField();
            grantPopup.getField('stopReason').allowBlank = false;
        } else {
            grantPopup.getField('stopReason').allowBlank = true;
			grantPopup.getField('stopReason').hide();
        }
		
		if (grantPopup.rendered) {
			grantPopup.syncSize();
		}
    }

    function updateStopDateForGrantStatus(grantStatus) {
        var grantPopup = _resources.popups['grantMaint'];
        var grantType = grantPopup.getField('grantType').getValue();
        var grantRec = _resources.grids['grants'].getSelectedRecord();

        if (grantType == _GRANTTYPE_QESI && grantStatus == 'Stopped')
            grantPopup.getField('stopDate').setValue(getCurrentBusDate());
        else if (grantPopup.action === _self.MOD) {
          if (grantType == _GRANTTYPE_ADDCESG) {
            if(grantStatus === 'Requested') 
              grantPopup.getField('stopDate').setValue(DesktopWeb.Util.getDateDisplayValue(getDefaultStopDate(grantType)));            
          } 
        }
    }

    function getCurrentBusDate() {
        return DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML,
                                                                         '//DefaultValues/currentBusDate'));
    }

    function getGrantStartDate(grantType) {
        var grantStartDateTag = '';
        var grantStartDate = '';
        
        if (grantType === _GRANTTYPE_BCTESG) {
            grantStartDateTag = 'bctesgEffDate';
        } else if (grantType === _GRANTTYPE_SAGES) {
            grantStartDateTag = 'sagesEffDate';
        }
         else if (grantType === _GRANTTYPE_ADDCESG) {
            grantStartDateTag = 'addcesgEffDate';
        }
        
        if (grantStartDateTag != '')
            grantStartDate = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML,
                                                                              '//DefaultValues/' + grantStartDateTag));
        return grantStartDate;
    }
    
    function getDefaultStopDate (grantType) {
      return IFDS.Xml.getNodeValue(
              _currentBenefGrantInfoXML,
              '//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + grantType + '"]/defaultStopDate'
             );
    }

    function storeContextErrors(errorNodes) {
        clearContextErrors();

        var firstErrRecIndex = -1;
        for (var i = 0; i < errorNodes.length; i++) {
            var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
            
            if (table == "GrantDetail") {
                var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
                var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');

                // Update grid
                var recordIndex = _resources.grids['grants'].getStore().find('grantInfoUUID', uuid);
                var grantDetlRecord = _resources.grids['grants'].getStore().getAt(recordIndex);

                grantDetlRecord.set('errMsg', errMsg);
                _resources.grids['grants'].getStore().commitChanges();
                
                if (firstErrRecIndex == -1)
                    firstErrRecIndex = recordIndex;
            }
        }

        if (firstErrRecIndex == -1) {
            _resources.grids['grants'].getSelectionModel().selectFirstRow();
        } else {
            _resources.grids['grants'].getSelectionModel().selectRow(firstErrRecIndex);
            _resources.grids['grants'].focusRow(firstErrRecIndex);
        }
    }

    function clearContextErrors() {
        var errRecords = _resources.grids['grants'].getStore().queryBy(function(record){
                                                                           return record.get('errMsg') != "";
                                                                       });

        for (i = 0; i < errRecords.length; i++) {
            errRecords.itemAt(i).set('errMsg', '');
            errRecords.itemAt(i).commit();
        }
    }

    function getGrantTypeOptionAddList() {
    	var currentDate = DesktopWeb.Util.stringToDate(getCurrentBusDate(), 
    			DesktopWeb.Util.getDateDisplayFormat());
    	var grantTypeOptionLists = IFDS.Xml.getNodes(_currentBenefGrantInfoXML, 
				'//Beneficiary/List[@listName="GrantTypeOption"]/Element');
		var xml = IFDS.Xml.newDocument("List");
		
		IFDS.Xml.addAttribute(IFDS.Xml.getNode(xml, "."), "listName", "GrantTypeOptionAdd");
		
    	if (!Ext.isEmpty(currentDate)) {
			for (i = 0; i < grantTypeOptionLists.length; i++) {
				var grantStopDate = DesktopWeb.Util.stringToDate(
						IFDS.Xml.getNodeValue(grantTypeOptionLists[i], "grantStopDate"), 
						DesktopWeb.Util.getDateSmartviewFormat());
				if (!Ext.isEmpty(grantStopDate)) {
					// exclude the expire grant (grantStopDate passed)
					if ((currentDate.getTime() <= grantStopDate.getTime())) {
						IFDS.Xml.appendNode(xml, IFDS.Xml.cloneDocument(grantTypeOptionLists[i]));
					}
				} else {
					// if grantStopDate is null or empty, include the grant (assume grantStopDate = 9999/12/31).
					IFDS.Xml.appendNode(xml, IFDS.Xml.cloneDocument(grantTypeOptionLists[i]));
				}
			} 
    	}
    	return xml;	
	}
    
    function selectRetroactiveChange(retroactive) {
    	var grantPopup = _resources.popups['grantMaint'];
    	if (retroactive == 'RT511') {
        	var minStartDateRT511 = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, 
        		'//DefaultValues/minStartDateRT511'));
        	grantPopup.getField('effectiveDate').setValue(minStartDateRT511);
        } else {
			if (grantPopup.action === _self.ADD || grantPopup.isModifyingNewRec){
				var defaultStartDate = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_currentBenefGrantInfoXML,
					'//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + _GRANTTYPE_ADDCESG + '"]/defaultStartDate'));
				grantPopup.getField('effectiveDate').setValue(defaultStartDate);
			}
        }
    }

    // PUBLIC ITEMS *************************************
    return {
        ADD: 'add'
        ,MOD: 'mod'
        ,DEL: 'del'

        ,updatesFlag: false

        ,init: function(res) {
            _resources = res;
            _self = DesktopWeb._SCREEN_CONTROLLER;

            var viewParamXML = IFDS.Xml.newDocument("data");
            IFDS.Xml.addSingleNode(viewParamXML, 'runMode', 'init');
            IFDS.Xml.addSingleNode(viewParamXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
            IFDS.Xml.addSingleNode(viewParamXML, 'benefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);


            DesktopWeb.Ajax.doSmartviewAjax(_initView,
                                            null, viewParamXML,
                                            responseHandler,
                                            _translationMap['ProcMsg_Loading']);

            function responseHandler(success, responseXML) {
				if (success) {
					_initDataXML = responseXML;
                    _currentBenefGrantInfoXML = responseXML;
                    populateScreen();
                }
            }
        }

        ,getDisplay: function(listName, code) {
            return getDisplay(listName, code);
        }

        ,handleGrantSelectChange: function() {
            var selectedRecord = _resources.grids['grants'].getSelectedRecord();

            if (selectedRecord) {
                // Add Button
                if (_addPerm) {
                    _resources.grids['grants'].enableButton('addBtn');
                } else {
                    _resources.grids['grants'].disableButton('addBtn');
                }

                // Historical and Admin buttons
                if (selectedRecord.data['runMode'] === _self.ADD) {
                    _resources.grids['grants'].disableButton('historicalBtn');
                    _resources.grids['grants'].disableButton('adminBtn');
                } else {
                    _resources.grids['grants'].enableButton('historicalBtn');
                    _resources.grids['grants'].enableButton('adminBtn');
                }

                // Modify Button
                if (selectedRecord.data['runMode'] === _self.ADD || (_modPerm && selectedRecord.data['modPerm'])) {
                    _resources.grids['grants'].enableButton('modBtn');
                } else {
                    _resources.grids['grants'].disableButton('modBtn');
                }

                // Delete Button
                if (selectedRecord.data['runMode'] == _self.ADD) {
                    _resources.grids['grants'].enableButton('delBtn');
                } else {
                	if (selectedRecord.data['delPerm'] === 'yes' && _delPerm) {
                    	_resources.grids['grants'].enableButton('delBtn');
                    } else {
                    	_resources.grids['grants'].disableButton('delBtn');
                    }
                }

                // Additional Grant Panel
                var dispRetroactive = getDisplay('RetroactiveList', selectedRecord.data['retroactive']);
                var dispGrantOption = getDisplay('ACESYearOptions', selectedRecord.data['grantOption']);
                var dispGrantYear = selectedRecord.data['grantYear'];

                _resources.fields['AdditionalGrantInfo']['retroactive'].setValue(dispRetroactive);
                _resources.fields['AdditionalGrantInfo']['age'].setValue(dispGrantOption);
                _resources.fields['AdditionalGrantInfo']['grantYear'].setValue(dispGrantYear);

                if (dispRetroactive === '')
                    _resources.fields['AdditionalGrantInfo']['retroactive'].hideField();
                else
                    _resources.fields['AdditionalGrantInfo']['retroactive'].showField();

                if (dispGrantOption === '')
                    _resources.fields['AdditionalGrantInfo']['age'].hideField();
                else
                    _resources.fields['AdditionalGrantInfo']['age'].showField();

                if (dispGrantYear === '')
                    _resources.fields['AdditionalGrantInfo']['grantYear'].hideField();
                else
                    _resources.fields['AdditionalGrantInfo']['grantYear'].showField();

                // Hide Group Panel
                if (dispRetroactive === '' && dispGrantOption === '' && dispGrantYear === '')
                    _resources.layout.get('addtionalInfoPanel').hide();
                else
                    _resources.layout.get('addtionalInfoPanel').show();
            } else {
                _resources.grids['grants'].disableButton('modBtn');
                _resources.grids['grants'].disableButton('delBtn');
                _resources.grids['grants'].disableButton('historicalBtn');
                _resources.grids['grants'].disableButton('adminBtn');
            }
        }

        ,openActionPopup: function (popupScreen, action) {
            var popup = _resources.popups[popupScreen];

            if (popupScreen === 'grantMaint') {
                //Dropdown List
            	var listGrantTypeOption = null;
            	
                if (action === _self.ADD) {
                	listGrantTypeOption = _listGrantTypeOption_add;
                } else {
                	listGrantTypeOption = IFDS.Xml.getNode(_currentBenefGrantInfoXML, 
                                                           '//Beneficiary/List[@listName="GrantTypeOption"]');
                }

                popup.getField('grantType').loadData(listGrantTypeOption);
                popup.getField('stopReason').loadData(IFDS.Xml.getNode(_initDataXML,
                                                                       '//List[@listName="StopReasonList"]'));
                popup.getField('retroactive').loadData(IFDS.Xml.getNode(_initDataXML,
                                                                        '//List[@listName="RetroactiveList"]'));
                
                                  
                popup.init(action);
                popup.show();
                
                popup.getField('respBenef').setValue(IFDS.Xml.getNodeValue(_currentBenefGrantInfoXML,
                                                                           '//Beneficiary/BenefInfo/name'));
            }
        }

        ,validateScreen : function () {
            var isValid = true;

            return isValid;
        }


        ,ReloadBenefInfoAndGrantInfo: function () {
            ReloadBenefInfoAndGrantInfo();
        }

        ,openHistoricalPopup: function () {
            var viewParam = {};
            var title = _translationMap['GrantInformation'] + "-" + _translationMap['History']
            
            viewParam['auditType'] = 'RESPGrant';
            viewParam['searchValue1'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum']
            viewParam['searchValue2'] = _resources.fields['benefCMB'].getValue();
            viewParam['searchValue5'] = _resources.grids['grants'].getSelectedRecord().data['respGrantInfoID'];

            _resources.popups['history'].init(title, _historicalView, viewParam, true);
            _resources.popups['history'].show();
        }

        ,openAdminPopup: function () {
            var title = null;
            var selectedRecord = null;

            selectedRecord = _resources.grids['grants'].getSelectedRecord();
            title = _translationMap['GrantInformation']+ ' - ' +_translationMap['Admin']

            var adminData = {};
            adminData['userName'] = selectedRecord.get('userName');
            adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('processDate'));
            adminData['modUser'] = selectedRecord.get('modUser');
            adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));

            _resources.popups['admin'].init(title, adminData);
            _resources.popups['admin'].show();
        }

        ,doUpdate: function () {
            var updateStatus = null;
            var updateXML = buildUpdateXML();

            DesktopWeb.Ajax.doSmartviewUpdate(_updateView,
                                              null, updateXML,
                                              responseHandler,
                                              _translationMap['ProcMsg_Saving']);

            function responseHandler(success, responseXML, contextErrors) {
                if (success) {
                    updateStatus = DesktopWeb._SUCCESS;
                } else {
					storeContextErrors(contextErrors);
                    updateStatus = DesktopWeb._FAIL
                }
            }
            return updateStatus;
        }

        ,confirmAndCommitScreen: function () {

            DesktopWeb.Util.commitScreen();

            function confirmCancelRequest(buttonId) {
                if (buttonId === 'ok') {
                    DesktopWeb.Util.commitScreen();
                }
            }
        }
		
		,loadGrantStatusList: function (popup, grantType, grantStatus, origGrantStatus) {
			if (grantType !== '' ) {
				// Grant Status
                var grantStatusNode = IFDS.Xml.getNode(
                                           _initDataXML,
                                           '//StatusOptions/List[@listName="' + grantType + origGrantStatus + '"]');
				
				
				/** TODO: Load grant status list here **/
				if (grantStatusNode != null && grantStatus != 'New' && popup.action != _self.ADD && popup.isModifyingNewRec == false) {
					grantStatusNode = loadCurrentStatusList(IFDS.Xml.cloneDocument(grantStatusNode), grantStatus, origGrantStatus);
				}
				
				function loadCurrentStatusList(grantStatusListXML, status, origStatus) {
					var passiveStatus = IFDS.Xml.getNodeValue(_initDataXML, '//List[@listName="PassiveStatus"]/Element[code="' + origStatus + '"]/value');
					var statusDescNode = IFDS.Xml.getNode(grantStatusListXML, '//List/Element[code="' + origStatus + '"]/value');
					
					IFDS.Xml.setNodeValue(statusDescNode, passiveStatus);
					
					return grantStatusListXML;
				}
				
                if (grantStatusNode != null) {
                    popup.getField('grantStatus').loadData(grantStatusNode);
                } else {
                	popup.getField('grantStatus').getStore().removeAll();
                }
				
                if (popup.action === _self.ADD) {
                    if (!popup.isModifyingNewRec) {
                        popup.getField('grantStatus').setValue('Requested');
                        selectGrantStatusChange(grantType, 'Requested');
                    }

                    if (grantType === _GRANTTYPE_SAGES) {
					    popup.getField('grantStatus').enableField();
					} else {
                        popup.getField('grantStatus').disableField();
					}

                } else {
                    popup.getField('grantStatus').enableField();
                }
                
                if (grantStatus === 'Pending') {
                	popup.getField('grantStatus').disableField();
                }
            }
		}

        ,selectGrantType: function (grantType) {
            var grantPopup = _resources.popups['grantMaint'];
			
			var defaultStopDate = IFDS.Xml.getNodeValue(
                   _currentBenefGrantInfoXML,
                   '//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + grantType + '"]/defaultStopDate'
                   );
            var defaultStartDate = IFDS.Xml.getNodeValue(
                   _currentBenefGrantInfoXML,
                   '//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + grantType + '"]/defaultStartDate'
                   );

            // Stop date
            if (grantPopup.action === _self.ADD) {
                if (grantType === '') {
                    grantPopup.getField('stopDate').setValue(DesktopWeb.Util.getDateDisplayValue("12/31/9999"));
                } else if (!grantPopup.isModifyingNewRec) {
                    grantPopup.getField('stopDate').setValue(DesktopWeb.Util.getDateDisplayValue(defaultStopDate));
                }

                grantPopup.getField('stopDate').enableField();
                
            } else if (grantPopup.action == _self.MOD) {
                if (getGrantRequestType(grantType) === _GRANT_PERIOD || 
                    getGrantRequestType(grantType) === _GRANT_ONETIME ||
                    getGrantRequestType(grantType) === _GRANT_YEAR)	{
                    grantPopup.getField('stopDate').enableField();
                } else {
                    grantPopup.getField('stopDate').disableField();
                }
            }

            //Effective Date
            var updateRelatedFieldsForEffDate = false;
            if (grantPopup.action === _self.ADD && !grantPopup.isModifyingNewRec) {
               grantPopup.getField('effectiveDate').allowBlank = true;
               grantPopup.getField('effectiveDate').setValue(grantType == '' ? 
                                          getCurrentBusDate() : DesktopWeb.Util.getDateDisplayValue(defaultStartDate));
               grantPopup.getField('effectiveDate').allowBlank = false;
               updateRelatedFieldsForEffDate = true;
            }

            if (grantPopup.action == _self.ADD || grantPopup.action == _self.MOD) {
                if (grantType === _GRANTTYPE_SAGES ||
                    grantType === _GRANTTYPE_BCTESG ||
                    grantType === _GRANTTYPE_ADDCESG) {
                    grantPopup.getField('effectiveDate').enableField();
                } else {
                    grantPopup.getField('effectiveDate').disableField();
                }
            } else {
                grantPopup.getField('effectiveDate').disableField();
            }
            effectiveDateChange(updateRelatedFieldsForEffDate);

            // Year
			if (getGrantRequestType(grantType) === _GRANT_YEAR && grantType === _GRANTTYPE_QESI) {
                grantPopup.getField('year').enableField();
                grantPopup.getField('year').showField()
                grantPopup.getField('year').allowBlank = false;
            } else {
                grantPopup.getField('year').disableField();
                grantPopup.getField('year').hideField();
                grantPopup.getField('year').clearField();
                grantPopup.getField('year').allowBlank = true;
            }
			
			
            // Retroactive Addtional CESG
			grantPopup.getField('retroactive').setValue('');
            if (grantType === _GRANTTYPE_ADDCESG) {
				grantPopup.getField('retroactive').showField();
            } else {
                grantPopup.getField('retroactive').hideField();
            }

            if (grantPopup.rendered) {
                grantPopup.syncSize();
            }
        }

        ,selectGrantStatusChange: function (grantType, grantStatus) {
            selectGrantStatusChange(grantType, grantStatus);
        }

        ,updateStopDateForGrantStatus: function (grantStatus) {
            updateStopDateForGrantStatus(grantStatus);
        }

        ,effectiveDateChange: function (isUpdateRelatedFields) {
            effectiveDateChange(isUpdateRelatedFields);
        }

        ,validateGrant: function (data, action) {
            validateGrant(data, action);
        }
        
        ,populateGrantTypeFilterDropdown: function() {
            populateGrantTypeFilterDropdown();
        }

        ,getCurrentBusDate: function() {
            return getCurrentBusDate();
        }

        ,getGrantStartDate: function(grantType) {
            return getGrantStartDate(grantType);
        }

        ,getNewUUID: function () {
            return ++_latestUUID;
        }
        
        ,getGrantRequestType: function(grantType) {
            return getGrantRequestType(grantType);
        }
        
        ,getGrantStatusTranslation: function(record) {
			var grantStatusTrans = null;
			if (record.data['grantStat'] == record.data['origGrantStat']) {
				grantStatusTrans = IFDS.Xml.getNodeValue(
										_initDataXML, 
										'//List[@listName="PassiveStatus"]/Element[code="' + record.data['grantStat'] + '"]/value');
			} else {
				grantStatusTrans = IFDS.Xml.getNodeValue(
                                       _initDataXML,
                                       '//StatusOptions/List[@listName="' + record.data['grantType'] + record.data['origGrantStat'] + '"]/' + 
                                       'Element[code="' + record.data['grantStat'] + '"]/value'
                                    );
			}
                                    
            return grantStatusTrans == '' ? record.data['grantStat']:grantStatusTrans;
        }
        
        ,getDefaultStartDate: function(grantType) {
            return IFDS.Xml.getNodeValue(
                   _currentBenefGrantInfoXML,
                   '//Beneficiary/List[@listName="GrantTypeOption"]/Element[code="' + grantType + '"]/defaultStartDate'
                   );
        }
        
        ,getDefaultStopDate: function(grantType) {
            return getDefaultStopDate(grantType);
        }
        
        ,selectRetroactiveChange: function (retroactive) {
        	selectRetroactiveChange(retroactive);
        }
    }
}