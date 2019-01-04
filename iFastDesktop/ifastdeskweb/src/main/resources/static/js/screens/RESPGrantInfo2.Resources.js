/*********************************************************************************************
 * @file    RESPGrantInfo2.Resources.js
 * @author    Rod Walker
 * @desc    Resources JS file for RESP Grant Information screen.
 *
 * History: 
 *  16 Jul 2015 Aurkarn Mongkonrat P0241773 T81086
 *                    - Redesign the whole screen to be more flexible for the new grants.
 *
 *  21 Jul 2015 Aurkarn Mongkonrat P0241773 T81123
 *                    - Fix issues from T81086 issue log
 *
 *  18 Sep 2015 Aurkarn Mongkonrat P0241773 T81293
 *                    - Change Screen layout to fit French Translation
 *
 *  20 Oct 2015 Aurkarn Mongkonrat P0241773 T81559 DFT0054910
 *					  - Add effective date validation for SAGES and ADDCESG.
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
 *
 *  03 Dec 2015 Aurkarn Mongkonrat P0241773 T81814 DFT0057065 
 *					  - Append RESPGrantInfoID tag.
 *
 *  21 Dec 2015 Narin Suanlamyai P0241773 T81920 DFT0057786
 *					  - Update translation for grant pop-up title.
 *
 *  28 Dec 2015 Aurkarn Mongkonrat P0241773 T81957 DFT0057748 DFT0057843
 *					  - Enable stopdate field for all grant types and implement its validations.
 *
 *  22 Dec 2015 Nopphawan Hatthaseriphong P0250179 T81941
 *					  - Ability to delete RESP grant request information
 *
 *  18 Jan 2016 Nopphawan Hatthaseriphong P0250179 T82031 DFT0058503
 *					  - Add reject reason code and stop reason code to Grant info-Refused field
 *
 *  21 Jan 2016 Nopphawan Hatthaseriphong P0250179 T82057 DFT0058662 DFT0058748
 *					  - Fix grant status inside grid not translated.
 *
 *	13 May 2016 Aurkarn M. P0241773 DFT0062785 T82820
 *					  - Fix issue where BCTESG Grant Status reason not refreshed 
 *                      when status is changed.
 *                    - Fix issue where start and stop date of QESI is incorrect
 *                      when changing GrantYear
 *
 *  27 May 2016 Busarakorn S. P0241773 INC0029783 CHG0045600 INC0029000 CHG45602 T82937 R16.4 QV3
 *                    - Not validate stopdate < currentBusDate for Grant Year .
 *                    - Check same year when Add Grant year .
 *
 *  31 Oct 2016 Nopphawan Hatthaseriphong P0241773 T84157 INC0031814
 *              - Update the effective date for ADCESG when RT511 is indicated
 *                (add new function selectRetroactiveChange).
 *                The effective date is sent from back-end as 'minStartDateRT511'.
 *                
 *  23 Feb 2017 Narin Suanlamyai P0256094 T84842 DFT0070268
 *              - Fixed grant status with active/passive words.
 *                
 *********************************************************************************************/

DesktopWeb.ScreenResources = function (ctrlr) {
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    var _GRANT_YEAR = 'GrantYear';
    var _GRANTTYPE_QESI = 'QESI';
    var _GRANTTYPE_ADDCESG = 'ADDCESG';
    var _GRANTTYPE_CESG = 'CESG';
    var _GRANTTYPE_SAGES = 'SAGES';
    var _GRANTTYPE_BCTESG = 'BCTESG';
    var _GRANTTYPE_CLB = 'CLB';

    // content dimensions
    var _layoutHeight = 670;
    var _layoutWidth = 680;

    // **** buttons ****
    var _buttons = {

    }

    // **** fields ****
    var _fields = {
        benefCMB: new DesktopWeb.Controls.SMVComboBox({
            fieldLabel: _translationMap['BeneficiaryCMB']
            ,editable: true
            ,width: 250
            ,listeners: {
                select: function (combo, record, index) {
                    _controller.ReloadBenefInfoAndGrantInfo();
                }
            }
        })
        ,grantTypeCMB: new DesktopWeb.Controls.ComboBox({
            fieldLabel: _translationMap['GrantTypeCMB']
            ,store: new Ext.data.ArrayStore({
                fields: ['grantType', 'grantTypeDesc']
            })
            ,valueField: 'grantType'
            ,displayField: 'grantTypeDesc'
            ,editable: true
            ,width: 150
            ,listeners: {
                select: function (combo, record, index) {
                    var filter = combo.getValue();

                    if (filter == "All")
                        _grids['grants'].getStore().clearFilter();
                    else
                        _grids['grants'].getStore().filter('grantType', combo.getValue());
                    
                    if (_grids['grants'].getStore().getCount() > 0) {
                        _grids['grants'].getSelectionModel().selectFirstRow();
                    }
                }
            }
        })
        ,sin: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['SIN']
            ,width: 100
        })
        ,dob: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['DateOfBirth']
            ,width: 100
        })
        ,taxjuris: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['TaxJurisdiction']
            ,width: 100
        })
        ,taxTypeDesc: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['TaxType']
            ,width: 100
        })
        ,siblingOnly: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['SiblingOnly']
            ,width: 100
        })
        ,specimenNum: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['SpecimenNum']
            ,width: 100
        })
        ,beneAddr: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['Address']
            ,width: 400
        })

        ,pcgName: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['Name']
            ,width: 200
        })
        ,pcgSINBN: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap['SIN_BN']
            ,width: 75
        })
        ,AdditionalGrantInfo: {
            retroactive: new DesktopWeb.Controls.Label({
                fieldLabel: _translationMap['Retroactive']
                ,width: 100
            })
            ,age: new DesktopWeb.Controls.Label({
                fieldLabel: _translationMap['Age']
                ,width: 100
            })
            ,grantYear: new DesktopWeb.Controls.Label({
                fieldLabel: _translationMap['GrantYear']
                ,width: 100
            })
        }
    }

    // **** grids ****
    var _grids = {
        grants: new DesktopWeb.AdvancedControls.GridPanel({
            autoScroll: true
            ,height: 225
            ,autoExpandColumn: 'RejStopReason'
            ,store: new Ext.data.XmlStore({
                record: 'GrantDetail'
                ,fields: ['errMsg',
                          'runMode',
                          'grantType',
                          'grantTypeDesc',
                          'origGrantStat',
                          'grantStat',
                          'eligDate',
                          'stopDate',
                          'rejReason',
                          'stopReason',
                          'retroactive',
                          'grantOption',
                          'grantYear',
                          'modPerm',
                          'modDate',
                          'modUser',
                          'userName',
                          'processDate',
                          'grantInfoUUID',
                          'respGrantInfoID',
                          'delPerm',
                          'version']
                ,listeners: {
                    load: function (store, records) {
                        Ext.each(records, function (record) {
                            record.data['grantType'] = record.data['grantType'].toUpperCase();
							record.data['origGrantStat'] = record.data['grantStat'];
                            record.data['eligDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['eligDate']);
                            record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);
                            record.data['processDate']=DesktopWeb.Util.getDateDisplayValue(record.data['processDate']);
                        });
                        store.filterBy(function(record){return record.data.runMode != _controller.DEL});
                    }
                    ,update: function (store) {
                        store.filterBy(function(record){return record.data.runMode != _controller.DEL});
                    }
                }
            })
            ,selModel: new Ext.grid.RowSelectionModel({
                singleSelect: true
                ,listeners: {
                    rowselect: function (selModel, index, record) {
                        _controller.handleGrantSelectChange();
                    }
                    ,rowdeselect: function () {
                        _controller.handleGrantSelectChange();
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel({
                defaults: {
                    menuDisabled: true
                }
                ,columns: [
                    {
                        id: 'errMsg'
                        ,width: 25
                        ,renderer: function (val) {
                            return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
                        }
                    }
                    ,{header: _translationMap['GrantTypeCol'], dataIndex: 'grantTypeDesc', width: 90}
                    ,{header: _translationMap['GrantStatus'], dataIndex: 'grantStat', width: 80
                        ,renderer: function(val, metaData, record) {
                            return _controller.getGrantStatusTranslation(record);
                        }
                     }
                    ,{header: _translationMap['EffectiveDate'], dataIndex: 'eligDate', width: 85}
                    ,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 85}
                    ,{id: 'RejStopReason',header: _translationMap['GrantReaRejRef']
                        ,renderer: function(val, metaData, record){
                            var RejStopDesc = '';

                            if (record.data['stopReason'] != undefined &&
                                    record.data['stopReason'] != null &&
                                    record.data['stopReason'] != '') {
                                RejStopDesc = record.data['stopReason'] + (record.data['stopReason'] == '' ? '':':') +
                                		_controller.getDisplay('StopReasonList', record.data['stopReason']);
                            }

                            if (record.data['rejReason'] != undefined &&
                                    record.data['rejReason'] != null &&
                                    record.data['rejReason'] != '' && 
                                    record.data['rejReason'] != '0') {
                                RejStopDesc = RejStopDesc + (RejStopDesc == '' ? '':',') +
                                		record.data['rejReason'] + (record.data['rejReason'] == '' ? '':':') +
                                        _controller.getDisplay('RejectReasonList', record.data['rejReason']);
                            }

                            return RejStopDesc;
                        }
                    }
                ]
            })
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    itemId: 'addBtn'
                    ,text: _translationMap['Add']
                    ,disabled: true
                    ,handler: function () {_controller.openActionPopup('grantMaint', _controller.ADD);}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'modBtn'
                    ,text: _translationMap['Modify']
                    ,disabled: true
                    ,handler: function () {_controller.openActionPopup('grantMaint', _controller.MOD);}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'delBtn'
                    ,text: _translationMap['Delete']
                    ,disabled: true
                    ,handler: function () {_controller.openActionPopup('grantMaint', _controller.DEL);}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'historicalBtn'
                    ,text: _translationMap['Historical']
                    ,disabled: true
                    ,handler: function () {_controller.openHistoricalPopup()}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'adminBtn'
                    ,text: _translationMap['Admin']
                    ,disabled: true
                    ,handler: function () {_controller.openAdminPopup();}
                })
            ]
        })
    }

    var _popups = {
        grantMaint: new DesktopWeb.AdvancedControls.PopupWindow({
            action: ''
            ,uuid: ''
            ,grantOption: ''
            ,rejReason: '0'
            ,isModifyingNewRec: false
            ,width: 320
            ,closeAction: 'hide'
            ,autoHeight: true
            ,modal: true
            ,defaults: {border:false}
            ,version: ''
            ,delPerm: ''
            ,items: [
                {
                    html: _translationMap['DeleteConfirmMsg']
                    ,style: 'text-align:center;font-weight:bold;'
                }
                ,{
                    layout: 'form'
                    ,style: 'padding:4px'
                    ,defaults: {border: true}
                    ,labelWidth: 110
                    ,items: [
                        new DesktopWeb.Controls.Label({
                            itemId: 'respBenef'
                            ,fieldLabel: _translationMap['RESPBenef']
                            ,allowBlank: true
                        })
                        ,new DesktopWeb.Controls.ComboBox({
                            itemId: 'grantType'
                            ,fieldLabel: _translationMap['GrantTypePopup']
                            ,width: 150
                            ,editable: true
                            ,allowBlank: false
                            ,valueField: 'code'
                            ,displayField: 'value'
                            ,store: new Ext.data.XmlStore({
                                record: 'Element'
                                ,fields: ['code', 'value']
                            })
                            ,listeners:{
                                select: function (fld, record, index) {
                                    _controller.selectGrantType(fld.getValue());
									_controller.loadGrantStatusList(_popups['grantMaint'], fld.getValue(), '', '');
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'grantStatus'
                            ,fieldLabel: _translationMap['GrantStatusPopup']
                            ,width: 150
                            ,editable: true
                            ,allowBlank: false
                            ,listeners:{
                                select: function (fld, record, index) {
                                    var grantType = _popups['grantMaint'].getField('grantType').getValue();
                                    
                                    _controller.selectGrantStatusChange(grantType, fld.getValue());
                                    _controller.updateStopDateForGrantStatus(fld.getValue());
                                    
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.DateField({
                            itemId: 'effectiveDate'
                            ,fieldLabel: _translationMap['EffectiveDate']
                            ,allowBlank: false
                            ,width: 150
                            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                            ,listeners:{
                                change: function (fld, record, index) {
                                    _controller.effectiveDateChange(true);
                                }
                            }
                            ,validator: function(value) {
                                var grantStatus = _popups['grantMaint'].getField('grantStatus').getValue();
                                var grantType = _popups['grantMaint'].getField('grantType').getValue();
                                    
                                if (value === '' && !this.allowBlank) {
                                    if (grantType === _GRANTTYPE_BCTESG) {
                                        if (grantStatus === 'Requested') {
                                            return _translationMap['ERR_BCTESG_EFF_DATE_BLANK_NULL_FOR_REQ'];
                                        } else {
                                            return _translationMap['ERR_REQUIRED_FIELD'];
                                        }
                                    } else {
                                        return _translationMap['ERR_REQUIRED_FIELD'];
                                    }
                                           
                                } else {
                                    var effDate = DesktopWeb.Util.stringToDate(value,
                                                                               DesktopWeb.Util.getDateDisplayFormat());
                                    var currentBusDate = DesktopWeb.Util.stringToDate(_controller.getCurrentBusDate(),
                                                                               DesktopWeb.Util.getDateDisplayFormat());

                                    if (grantType === _GRANTTYPE_BCTESG) {
                                        var bctesgEffDate = DesktopWeb.Util.stringToDate(
                                                                     _controller.getGrantStartDate(_GRANTTYPE_BCTESG),
                                                                     DesktopWeb.Util.getDateDisplayFormat());

                                        if (effDate < bctesgEffDate) {
                                            return _translationMap['ERR_BCTESG_EFF_DATE_CANNOT_BE_BEFORE'];
                                        } else if (effDate > currentBusDate) {
                                            return _translationMap['ERR_BCTESG_EFF_DATE_GREATER_THAN_SYSTEM_DATE'];
                                        }
                                    } else if (grantType === _GRANTTYPE_ADDCESG) {
                                        var addcesgEffDate = DesktopWeb.Util.stringToDate(
                                                                     _controller.getGrantStartDate(_GRANTTYPE_ADDCESG),
                                                                     DesktopWeb.Util.getDateDisplayFormat());
                                        if (effDate < addcesgEffDate) {
                                            return _translationMap['ERR_ADDCESG_EFF_DATE_CANNOT_BE_BEFORE'];
                                        } else if (effDate > currentBusDate) {
                                            return _translationMap['ERR_DEFF_CANNOT_FUTUREDATE'];
                                        }
                                    } else if (grantType === _GRANTTYPE_SAGES) {
                                        var sagesEffDate = DesktopWeb.Util.stringToDate(
                                                                   _controller.getGrantStartDate(_GRANTTYPE_SAGES),
                                                                   DesktopWeb.Util.getDateDisplayFormat());

                                        if (effDate < sagesEffDate) {
                                            return _translationMap['ERR_SAGES_EFF_DATE_CANNOT_BE_BEFORE'];
                                        } else if (effDate > currentBusDate) {
                                            return _translationMap['ERR_SAGES_EFF_DATE_GREATER_THAN_SYSTEM_DATE'];
                                        }
                                    }
                                }
                                
                                return true;
                            }
                        })
                        ,new DesktopWeb.Controls.DateField({
                            itemId: 'stopDate'
                            ,fieldLabel: _translationMap['StopDate']
                            ,allowBlank: false
                            ,width: 150
                            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                        })
                        ,new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'retroactive'
                            ,fieldLabel: _translationMap['RetroactivePopup']
                            ,width: 150
                            ,editable: true
                            ,allowBlank: true
                            ,hidden: true
                            ,listeners:{
                                select: function (fld, record, index) {
									var popup = _popups['grantMaint'];
									if (popup.action === _controller.ADD || popup.isModifyingNewRec){
										_controller.selectRetroactiveChange(fld.getValue());
									}
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.NumberField({
                            itemId: 'year'
                            ,fieldLabel: _translationMap['Year']
                            ,hidden: true
                            ,width: 150
                            ,allowBlank: true
                            ,decimalPrecision: 0
                            ,allowNegative: false
                            ,listeners:{
                                change: function (fld, record, index) {
                                    var grantType = _popups['grantMaint'].getField('grantType').getValue();
                                    
                                    if (grantType === _GRANTTYPE_QESI) {
                                        var startDate;
                                        var endDate;
                                        var defaultStartDate = _controller.getDefaultStartDate(grantType);
                                        var defaultStopDate = _controller.getDefaultStopDate(grantType);
                                        var yearOfDefStartDate = DesktopWeb.Util.stringToDate(defaultStartDate,
                                                                     DesktopWeb.Util.getDateDisplayFormat()).getYear();
                                                                  
                                        if (fld.getValue() == yearOfDefStartDate) {
                                            startDate = DesktopWeb.Util.getDateDisplayValue(defaultStartDate);
                                            endDate = DesktopWeb.Util.getDateDisplayValue(defaultStopDate);
                                        }
                                        else {
                                            startDate = DesktopWeb.Util.getDateDisplayValue('01/01/' + fld.getValue());
                                            endDate = DesktopWeb.Util.getDateDisplayValue('12/31/' + fld.getValue());
                                        }
                                        
                                        _popups['grantMaint'].getField('effectiveDate').setValue(startDate);
                                        _popups['grantMaint'].getField('stopDate').setValue(endDate);
                                    }
                                }
                            }
                        })
                        ,new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'stopReason'
                            ,fieldLabel: _translationMap['StopReason']
                            ,width: 150
                            ,editable: true
                            ,allowBlank: true
                        })
                    ]
                }
            ]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    itemId: 'okBtn'
                    ,text: _translationMap['OK']
                    ,handler: function () {
                        if (_popups['grantMaint'].action == _controller.DEL && 
                        		_popups['grantMaint'].isModifyingNewRec) {
                        	_grids['grants'].removeSelectedRecord();
                            _controller.populateGrantTypeFilterDropdown();
                            _popups['grantMaint'].hide();
                        } else {
                            if (_popups['grantMaint'].isValid() && _popups['grantMaint'].isBusinessValid()) {
                                _controller.validateGrant(_popups['grantMaint'].getData(), 
                                                          _popups['grantMaint'].action);
                            }
                        }
                    }
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'canBtn'
                    ,text: _translationMap['Cancel']
                    ,handler: function () {
                        _popups['grantMaint'].hide();
                    }
                })
            ]
            ,init: function (action) {
                // initialize popup based on action
                var popup = _popups['grantMaint'];
                popup.action = action;
                popup.isModifyingNewRec = false;

                switch (action) {
                    case _controller.ADD: {
                        popup.setTitle(_translationMap['GrantMaintTitleAdd']);
                        popup.populate(action);
                        popup.get(0).hide();
                        break;
                    }
                    case _controller.MOD: {
                        popup.setTitle(_translationMap['GrantMaintTitleModify']);
                        popup.populate(action);
                        popup.get(0).hide();
                        break;
                    }
                    case _controller.DEL: {
                        popup.setTitle(_translationMap['GrantMaintTitleDelete']);
                        popup.populate(action);
                        popup.disableAllFields();
                        popup.get(0).show();
                        break;
                    }
                }
            }
            ,populate: function (action) {
                var popup = _popups['grantMaint'];

                popup.clearAllFields();
                popup.enableAllFields();
                popup.customClearFields();

                if (action == _controller.ADD) {
                    _grids['grants'].clearSelectedRecord();
					popup.version = '1';
					popup.delPerm = 'yes';
                    popup.uuid = _controller.getNewUUID();
                    popup.getField('stopReason').hide();
					
					_controller.selectGrantType('');
					
                } else if (action == _controller.MOD) {
                    var grantRec = _grids['grants'].getSelectedRecord();
					
					popup.action = (grantRec.data['runMode'] === _controller.ADD) ? _controller.ADD : action;
					popup.isModifyingNewRec = grantRec.data['runMode'] === _controller.ADD;
					popup.version = grantRec.data['version'];
					popup.delPerm = grantRec.data['delPerm'];
					popup.rejReason = grantRec.data['rejReason'];
                    popup.uuid = grantRec.data['grantInfoUUID'];
                    popup.grantOption = grantRec.data['grantOption'];
					
                    // In case no grant description in the popup dropdown for selected record (Grid)
                    // we should add it to the dropdown manually
                    if (popup.getField('grantType').getStore().findExact('code', grantRec.data['grantType']) < 0) {
                        popup.getField('grantType').getStore().add(new Ext.data.Record({
                                                                                  code: grantRec.data['grantType'],
                                                                                  value: grantRec.data['grantTypeDesc']
                                                                  }));
                    }

                    popup.getField('grantType').disableField();
                    popup.getField('grantType').setValue(grantRec.data['grantType']);
					_controller.selectGrantType(grantRec.data['grantType']);
					
                    popup.getField('effectiveDate').setValue(grantRec.data['eligDate']);
                    popup.getField('stopDate').setValue(grantRec.data['stopDate']);
					
					_controller.loadGrantStatusList(popup, grantRec.data['grantType'], grantRec.data['grantStat'], grantRec.data['origGrantStat']);
					popup.getField('grantStatus').setValue(grantRec.data['grantStat']);
					_controller.selectGrantStatusChange(grantRec.data['grantType'], grantRec.data['grantStat']);
					
                    popup.getField('retroactive').setValue(grantRec.data['retroactive']);
                    popup.getField('stopReason').setValue(grantRec.data['stopReason']);
                    popup.getField('year').setValue(grantRec.data['grantYear']);
                } else if (action == _controller.DEL) {
                    var grantRec = _grids['grants'].getSelectedRecord();
					
					popup.action = _controller.DEL;
					popup.isModifyingNewRec = grantRec.data['runMode'] === _controller.ADD;
					popup.version = grantRec.data['version'];
					popup.delPerm = grantRec.data['delPerm'];
					popup.rejReason = grantRec.data['rejReason'];
					popup.uuid = grantRec.data['grantInfoUUID'];
					popup.grantOption = grantRec.data['grantOption'];
					popup.getField('grantType').disableField();
					popup.getField('grantType').setValue(grantRec.data['grantType']);
					popup.getField('effectiveDate').setValue(grantRec.data['eligDate']);
					popup.getField('stopDate').setValue(grantRec.data['stopDate']);
					popup.getField('grantStatus').setValue(grantRec.data['grantStat']);
					popup.getField('retroactive').setValue(grantRec.data['retroactive']);
					popup.getField('stopReason').setValue(grantRec.data['stopReason']);
					popup.getField('year').setValue(grantRec.data['grantYear']);

					_controller.selectGrantType(grantRec.data['grantType']);
                }

                if (popup.rendered) popup.syncSize();
            }
            ,isBusinessValid: function () {
                var popup = _popups['grantMaint'];
                var valid = true;		
				var grantType = popup.getField('grantType').getValue();
				var stopDate = popup.getField('stopDate').getValue();
                var currentBusDate = DesktopWeb.Util.stringToDate(_controller.getCurrentBusDate(),
                                                           DesktopWeb.Util.getDateDisplayFormat());
				var yearOfEffDate = '';
				var yearOfStopDate = stopDate.getYear(); 
				
				if (popup.getField('effectiveDate').getValue() != '') {
					yearOfEffDate = _popups['grantMaint'].getField('effectiveDate').getValue().getYear(); 
				}

                if (stopDate < currentBusDate &&
    				grantType != _GRANTTYPE_BCTESG &&
				    grantType != _GRANTTYPE_ADDCESG &&
					grantType != _GRANTTYPE_SAGES &&
					_controller.getGrantRequestType(grantType) != _GRANT_YEAR ) {
							
					valid = false;		
                    popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDTE']);
                }
				else if ((_controller.getGrantRequestType(grantType) === _GRANT_YEAR &&
                         popup.action == _controller.ADD) &&
				         yearOfEffDate != '' && 
						 yearOfStopDate != '' && 
						 yearOfEffDate != yearOfStopDate) {
				    valid = false;
				    popup.getField('stopDate').markInvalid( _translationMap['ERR_EFF_AND_STOP_MUST_BE_THE_SAME_YEAR']);
				}   

                if (popup.getField('effectiveDate').getValue() > popup.getField('stopDate').getValue()) {
                    valid = false;
                    
                    if (!popup.getField('effectiveDate').readOnly) {
                        popup.getField('effectiveDate').markInvalid(
                                                             _translationMap['ERR_DEFF_CANNOT_GREATER_THAN_STOPDATE']);
                    }
                    
                    if (!popup.getField('stopDate').readOnly) {
                        popup.getField('stopDate').markInvalid(
                                                             _translationMap['ERR_STOP_CANNOT_LESS_THAN_EFFDATE']);
                    }
                }

                return valid;
            }
            ,getData: function () {
                var popup = _popups['grantMaint'];
                var data = {};

                data['grantInfoUUID'] = popup.uuid;
                data['runMode'] = popup.action;
                data['grantOption'] = popup.grantOption;
                data['isModifyingNewRec'] = popup.isModifyingNewRec;

                data['grantType'] = popup.getField('grantType').getValue();
                data['grantTypeDesc'] = popup.getField('grantType').getRawValue();
                data['grantStat'] = popup.getField('grantStatus').getValue();
                data['eligDate'] = popup.getField('effectiveDate').getDisplayDateString();
                data['stopDate'] = popup.getField('stopDate').getDisplayDateString();
                data['grantYear'] = popup.getField('year').getValue();
                data['retroactive'] = popup.getField('retroactive').getValue();
                data['stopReason'] = popup.getField('stopReason').getValue();
                data['rejReason'] = popup.rejReason;
                
                data['version'] = popup.version;
                data['delPerm'] = popup.delPerm;

                return data;
            }
            ,customClearFields: function () {
                function fn(cmp)
                {
                    return (cmp.itemId != null && cmp.itemId.length != 0);
                }

                var fields = this.findBy(fn);
                var requriedFields = ['grantType', 'effectiveDate', 'stopDate', 'grantStatus'];

                for (var i = 0; i < fields.length; i++) {
                    if (fields[i].getValue() != '') {
                        fields[i].allowBlank = true;
                        fields[i].setValue('');
                        fields[i].allowBlank = requriedFields.indexOf(fields[i].itemId) < 0;
                    }
                }
            }
        })
        ,admin: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [
                {
                    layout: 'column'
                    ,style: 'padding:4px'
                    ,defaults: {border: false, labelWidth:80}
                    ,items: [
                        {
                            width: 185
                            ,layout: 'form'
                            ,defaults: {width:80}
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'userName'
                                    ,fieldLabel: _translationMap['Username']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'modUser'
                                    ,fieldLabel: _translationMap['ModUser']
                                })
                            ]
                        }
                        ,{
                            width: 185
                            ,layout: 'form'
                            ,defaults: {width: 80}
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'procDate'
                                    ,fieldLabel: _translationMap['ProcessDate']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'modDate'
                                    ,fieldLabel: _translationMap['ModDate']
                                    ,value: 'test'
                                })
                            ]
                        }
                    ]
                }
            ]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['OK']
                    ,handler: function () {
                        _popups['admin'].hide();
                    }
                })
            ]
            ,init: function(title, data) {
                this.setTitle(title);
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);
            }
        })
        ,history: new DesktopWeb.AdvancedControls.HistoryPopup()
    }

    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight

        ,fields: _fields

        ,buttons : _buttons

        ,grids: _grids

        ,popups: _popups

        ,layout: new Ext.Container({
            height: _layoutHeight
            ,width: _layoutWidth
            ,style: 'padding-left:5px; padding-right:5px;overflow-y:auto;'
            ,autoScroll: true
            ,items: [
                {
                    xtype: 'fieldset'
                    ,title: _translationMap['RESPBeneficiary']
                    ,id: 'beneFieldset'

                    ,items: [
                        {
                            layout: 'form'
                            ,labelWidth: 70
                            ,items: [
                                _fields['benefCMB']
                            ]
                        }
                        ,{
                            layout: 'column'
                            ,defaults: {
                                layout: 'form'
                                ,columnWidth: 0.33
                            }
                            ,items: [
                                {
                                    labelWidth: 65
                                    ,items: [
                                        _fields['sin']
                                        ,_fields['taxTypeDesc']
                                    ]
                                }
                                ,{
                                    labelWidth: 80
                                    ,items: [
                                        _fields['dob']
                                        ,_fields['siblingOnly']

                                    ]
                                }
                                ,{
                                    labelWidth: 90
                                    ,items: [
                                        _fields['taxjuris']
                                        ,_fields['specimenNum']
                                    ]
                                }
                            ]
                        }
                        ,{
                            layout: 'form'
                            ,labelWidth: 65
                            ,items: [
                                _fields['beneAddr']
                            ]
                        }
                    ]
                }
                ,{
                    xtype: 'fieldset'
                    ,title: _translationMap['PrimaryCareGiver_PCG']
                    ,layout: 'column'
                    ,defaults: {
                        layout: 'form'
                        ,labelWidth: 65
                    }
                    ,items: [
                        {
                            width: 550
                            ,items: [_fields['pcgName']]
                        }
                        ,{
                            width: 550
                            ,items: [_fields['pcgSINBN']]
                        }
                    ]
                }

                ,{
                    xtype: 'fieldset'
                    ,title: _translationMap['GrantGridTitle']
                    ,id: 'grantFieldSet'
                    ,labelWidth: 90
                    ,items: [
                        _fields['grantTypeCMB']
                        ,_grids['grants']
                    ]
                }
                ,{
                    xtype: 'fieldset'
                    ,title: _translationMap['AddtionalGrantInfo']
                    ,layout: 'column'
                    ,id: 'addtionalInfoPanel'
                    ,defaults: {
                        layout: 'form'
                    }
                    ,items: [
                        {
                            // Retroactive
                            layout: 'form'
                            ,columnWidth: 1.00
                            ,autoHeight:true
                            ,items: [
                                {
                                    layout: 'form'
                                    ,labelWidth: 190
                                    ,items: [_fields['AdditionalGrantInfo']['retroactive']]
                                }
                            ]
                        }
                        ,{
                            // Age
                            layout: 'form'
                            ,columnWidth: 1.00
                            ,autoHeight:true
                            ,items: [
                                {
                                    layout: 'form'
                                    ,labelWidth: 190
                                    ,items: [_fields['AdditionalGrantInfo']['age']]
                                }
                            ]
                        }
                        ,{
                            // Grant Year
                            layout: 'form'
                            ,columnWidth: 1.00
                            ,autoHeight:true
                            ,items: [
                                {
                                    layout: 'form'
                                    ,labelWidth: 190
                                    ,items: [_fields['AdditionalGrantInfo']['grantYear']]
                                }
                            ]
                        }
                    ]
                }
            ]
        })

        ,screenButtons: [
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['OK']
                ,handler: function () {
                    _controller.confirmAndCommitScreen();
                }
            })
            ,new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Cancel']
                ,handler: function () {
                    if (_controller.updatesFlag) {
                        DesktopWeb.Util.displayDiscardPrompt(callback)
                    } else {
                        callback(true);
                    }

                    function callback (discard) {
                        if (discard) {
                            DesktopWeb.Util.cancelScreen();
                        }
                    }
                }
            })
        ]
    }
}