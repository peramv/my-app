/*********************************************************************************************
 * @file    RegAgreement.Resources.js
 * @author  Hatthaseriphong, Nopphawan
 * @desc    Resources JS file of the Regulatory Agreement Maintenance
 *********************************************************************************************/
/*
 * Procedure: RegAgreement.Resources.js
 *
 * Purpose  : Resources for Regulatory Agreement Maintenance screen
 *
 * Notes    : - Regulatory Agreement Maintenance
 *            - Open screen from 
 *              Menu -> Broker Level Maintenance -> Regulatory Agreement Maintenance
 *
 * History  :
 *
 *    08 Feb 2017 N. Hatthaseriphong P0262306 CHG0048101 T85011 Regulatory Agreement Maintenance
 *        - Created
 *        
 *    29 Mar 2017 N. Hatthaseriphong P0262306 CHG0048101 T85188 Regulatory Agreement Maintenance
 *                DFT0073739 DFT0073746
 *        - Changed 'Pay Type' to 'Party Type'
 *        - Fixed calling _self to _controller 
 *
 *    05 Apr 2017 N. Hatthaseriphong P0262306 CHG0048101 T85240 Regulatory Agreement Maintenance
 *                DFT0073902
 *        - In searching area, retrieved all brokers (active and inactive) 
 *          for the broker suggest field.
 *        
 *    27 Feb 2017 Gomoot T. P0262306 CHG0048101 T85392 DFT0074488
 *        - Add logic to validate Effective date and stopdate
 *        
 *    19 Feb 2018 Matira P0268206-128 DFT0078815 DFT0080777
 *    		- Add Classification field in add/modify regulation popup
 *    		- Add Historical of Responsibility
 */

DesktopWeb.ScreenResources = function(ctrlr) {
  var _translationMap = DesktopWeb.Translation.getTranslationMap();
  var _controller = ctrlr;

  // content dimensions
  var _layoutWidth = 766;
  var _layoutHeight = 620;
  var _fieldSearchWidth = 275;
  var _fieldRegPopupWidth = 332;
  var _fieldResPopupWidth = 230;
  var _labelPopupWidth = 100;

  // ****** buttons ******
  var _buttons = {
    searchBtn: new DesktopWeb.Controls.ActionButton({
      text: _translationMap['Search'],
      style: "position:absolute; right:0px; top:0px;",
      handler: function() {
        if (_controller.doValidateSearch())
          _controller.doSearch(false);
      }
    })
  }

  // ****** fields ******
  var _fields = {
    regulationSrch: new DesktopWeb.Controls.SMVComboBox({
      itemId: 'regulationSrch',
      fieldLabel: _translationMap['Regulation'],
      editable: true,
      allowBlank: false,
      width: 150
    }),
    searchForSrch: new DesktopWeb.Controls.SMVComboBox({
      itemId: 'searchForSrch',
      fieldLabel: _translationMap["SearchFor"],
      editable: true,
      allowBlank: false,
      width: 150,
      listeners: {
        select: function(combo, record, index) {
          _controller.setSuggestService(record.data.code, 'mainScreen');
        }
      }
    }),
    searchForAll: new DesktopWeb.Controls.TextField({
      itemId: 'searchForAll',
      fieldLabel: _translationMap['SearchId'],
      width: _fieldSearchWidth,
      allowBlank: false
    // ,emptyText: _translationMap["EmptyText_All"]
    }),
    searchForBroker: new DesktopWeb.Controls.SuggestField({
      itemId: 'searchForBroker',
      fieldLabel: _translationMap["SearchId"],
      width: _fieldSearchWidth,
      smartview: 'brokerSearch',
      addtlSearchParams: [{
        valueFn: function() {
          return 'yes';
        }
      }],
      fields: ['displayValue', 'agencyCode', 'brokerDesc'],
      valueField: 'agencyCode',
      displayField: 'displayValue',
      hidden: true,
      allowBlank: false,
      emptyText: _translationMap["EmptyText_Broker"]
    }),
    searchForIntermediary: new DesktopWeb.Controls.SuggestField({
      itemId: 'searchForIntermediary',
      fieldLabel: _translationMap["SearchId"],
      width: _fieldSearchWidth,
      smartview: 'intrSearch',
      fields: ['intrCode', 'displayValue'],
      valueField: 'intrCode',
      displayField: 'displayValue',
      hidden: true,
      allowBlank: false,
      emptyText: _translationMap["EmptyText_Intermediary"]
    })
  } // _fields

  // ****** grids ******
  var _grids = {
    regulationGrid: new DesktopWeb.AdvancedControls.GridPanel({
      width: _layoutWidth,
      height: 235,
      autoScroll: true,
      store: new Ext.data.XmlStore({
        record: 'RegAgrmt',
        fields: ['regAgrmtUUID', 'regulationCode', 'regulationDesc',
            'partyType', 'partyDesc', 'partyCode', 'partyCodeName',
            'startDate', 'stopDate', 'recvDate', 'status', 'statusDesc',
            'version', 'userName', 'processDate', 'modUser', 'modDate',
            'runMode', 'RegAgrmtDetlsXML', 'classification'],
        listeners: {
          load: function(store, records) {
            Ext.each(records, function(record) {
              var node = IFDS.Xml.getNode(store.reader.xmlData,
                  "/*//RegAgrmt[regAgrmtUUID='" + record.data.regAgrmtUUID
                      + "']/RegAgrmtDetls");
              record.data.RegAgrmtDetlsXML = (node != null) ? IFDS.Xml
                  .serialize(node) : _controller.BLANK;
              record.data.startDate = DesktopWeb.Util
                  .getDateDisplayValue(record.data.startDate);
              record.data.stopDate = DesktopWeb.Util
                  .getDateDisplayValue(record.data.stopDate);
              record.data.recvDate = DesktopWeb.Util
                  .getDateDisplayValue(record.data.recvDate);
            });
            store.fireEvent('datachanged', store);
            store.filterBy(function(record) {
              return record.data.runMode != _controller.RUNMODE_DEL;
            });
            _grids['regulationGrid'].getSelectionModel().selectFirstRow();
          }
        }
      }),
      selModel: new Ext.grid.RowSelectionModel({
        singleSelect: true,
        listeners: {
          rowselect: function(selModel, index, record) {
            _controller.selectRegulationAgreement(record, 0);
          }
        }
      }),
      colModel: new Ext.grid.ColumnModel({
        defaults: {
          menuDisabled: true
        },
        columns: [{
          header: _translationMap['Regulation'],
          id: 'regulationDesc',
          dataIndex: 'regulationDesc',
          width: 90
        }, {
          header: _translationMap['PartyType'],
          id: 'partyDesc',
          dataIndex: 'partyDesc',
          width: 70
        }, {
          header: _translationMap['Code'],
          id: 'partyCode',
          dataIndex: 'partyCode',
          width: 60
        }, {
          header: _translationMap['Name'],
          id: 'partyCodeName',
          dataIndex: 'partyCodeName',
          width: 140
        }, {
          header: _translationMap['Classification'],
          id: 'classification',
          dataIndex: 'classification',
          width: 120,
          renderer: function(value,metadata,record)
          {
              return _controller.getDescription('FFIList', value);
          }
        }, {
          header: _translationMap['StartDate'],
          id: 'startDate',
          dataIndex: 'startDate',
          width: 80
        }, {
          header: _translationMap['StopDate'],
          id: 'stopDate',
          dataIndex: 'stopDate',
          width: 80
        }, {
          header: _translationMap['Status'],
          id: 'statusDesc',
          dataIndex: 'statusDesc',
          width: 100
        }]
      }),
      buttons: [
          new DesktopWeb.Controls.ActionButton({
            itemId: 'addBtn',
            text: _translationMap['Add'],
            handler: function() {
              _controller.openRegPopupAdd(_controller.RUNMODE_ADD,
                  'regulationPopup');
            }
          }),
          new DesktopWeb.Controls.ActionButton(
              {
                itemId: 'modBtn',
                text: _translationMap['Modify'],
                handler: function() {
                  _controller
                      .openRegPopupMod(
                          _controller.RUNMODE_MOD,
                          (_grids['regulationGrid'].getSelectedRecord().data['regAgrmtUUID']));
                }
              }),
          new DesktopWeb.Controls.ActionButton({
            itemId: 'delBtn',
            text: _translationMap['Delete'],
            hidden: true,
            handler: function() {
              DesktopWeb.Util.displayYesNo(
                  _translationMap['DeleteConfirmMsg'], handlePromptMsg);
              function handlePromptMsg(btn) {
                if (btn == 'yes')
                  _controller.doSave(_controller.RUNMODE_DEL, null);
                else
                  return;
              }

            }
          }), new DesktopWeb.Controls.ActionButton({
            itemId: 'moreBtn',
            text: _translationMap['More'],
            handler: function() {
              _controller.doSearch(true);
            }
          }), new DesktopWeb.Controls.ActionButton({
            itemId: 'adminBtn',
            text: _translationMap['Admin'],
            handler: function() {
              _controller.openAdminPopup();
            }
          }), new DesktopWeb.Controls.ActionButton({
            itemId: 'historicalBtn',
            text: _translationMap['Historical'],
            handler: function() {
              _controller.openHistoryPopup("RegulatoryAgrmt");
            }
          })]
    }) // regulationGrid
    ,
    responsibilityGrid: new DesktopWeb.AdvancedControls.GridPanel({
      width: 755,
      height: 235,
      autoScroll: true,
      store: new Ext.data.XmlStore({
        record: 'RegAgrmtDetl',
        fields: ['regAgrmtUUID', 'regAgrmtDetlUUID', 'acctAbility',
            'acctAbilityDesc', 'acctDes', 'acctDesDesc', 'acctParty',
            'acctPartyDesc', 'setAsDefault', 'setAsDefaultDesc', 'version'],
        listeners: {
          load: function(store, records) {
            store.fireEvent('datachanged', store);
          }
        }
      }),
      selModel: new Ext.grid.RowSelectionModel({
        singleSelect: true
      }),
      colModel: new Ext.grid.ColumnModel({
        defaults: {
          menuDisabled: true
        },
        columns: [{
          header: _translationMap['Responsibility'],
          id: 'acctAbilityDesc',
          dataIndex: 'acctAbilityDesc',
          width: 220
        }, {
          header: _translationMap['AccountDesignation'],
          id: 'acctDesDesc',
          dataIndex: 'acctDesDesc',
          width: 200
        }, {
          header: _translationMap['AccountableParty'],
          id: 'acctPartyDesc',
          dataIndex: 'acctPartyDesc',
          width: 163
        }, {
          header: _translationMap['SetByDefault'],
          id: 'setAsDefaultDesc',
          dataIndex: 'setAsDefaultDesc',
          width: 150
        }]
      }),
      buttons: [
    	  new DesktopWeb.Controls.ActionButton({
	        itemId: 'modBtn',
	        text: _translationMap['Modify'],
	        handler: function() {
	          _controller.openResPopupMod(_controller.RUNMODE_MOD);
	        }
    	  })
	      ,new DesktopWeb.Controls.ActionButton({
	          itemId: 'historicalBtn',
	          text: _translationMap['Historical'],
	          handler: function() {
	            _controller.openHistoryPopup("RegulatoryAgrmtDetl");
	          }
	      })
      ]
    }) // responsibilityGrid
  } // _grids

  // ****** popups ******
  var _popups = {
    regulationPopup: new DesktopWeb.AdvancedControls.PopupWindow({
      width: 520,
      autoScroll: true,
      action: null,
      closeAction: 'hide',
      title: '',
      modal: true,
      defaults: {
        border: false
      },
      items: [{
        layout: 'form',
        itemId: 'popup_main',
        style: 'padding:10px',
        border: false,
        labelWidth: _labelPopupWidth,
        items: [
            new DesktopWeb.Controls.SMVComboBox({
              itemId: 'pRegulationFld',
              fieldLabel: _translationMap["Regulation"],
              width: _fieldRegPopupWidth,
              editable: true,
              allowBlank: false
            }),
            new DesktopWeb.Controls.SMVComboBox({
              itemId: 'pPartyTypeFld',
              fieldLabel: _translationMap['PartyType'],
              width: _fieldRegPopupWidth,
              editable: true,
              allowBlank: false,
              listeners: {
                select: function(combo, record, index) {
                  _controller.setSuggestService(record.data.code,
                      'regulationPopup');
                }
              }
            }),
            new DesktopWeb.Controls.SuggestField({
              itemId: 'pBrokerFld',
              fieldLabel: _translationMap["PartyCode"],
              width: _fieldRegPopupWidth,
              smartview: 'brokerSearch',
              addtlSearchParams: [{
                name: 'onlyActive',
                valueFn: function() {
                  return 'yes';
                }
              }],
              fields: ['displayValue', 'agencyCode', 'brokerDesc'],
              valueField: 'agencyCode',
              displayField: 'displayValue',
              hidden: true,
              emptyText: _translationMap['EmptyText_Broker'],
              allowBlank: false,
              disableField: true
            }),
            new DesktopWeb.Controls.SuggestField({
              itemId: 'pIntermediaryFld',
              fieldLabel: _translationMap["PartyCode"],
              width: _fieldRegPopupWidth,
              smartview: 'intrSearch',
              fields: ['intrCode', 'displayValue'],
              valueField: 'intrCode',
              displayField: 'displayValue',
              hidden: true,
              emptyText: _translationMap['EmptyText_Intermediary'],
              allowBlank: false,
              disableField: true
            }),
            new DesktopWeb.Controls.TextField({
              itemId: 'pPartyCodeFld',
              fieldLabel: _translationMap['PartyCode'],
              width: _fieldRegPopupWidth,
              allowBlank: false,
              disableField: true,
              readOnly: true
            }),
            new DesktopWeb.Controls.ComboBox({
              itemId: 'pClassificationFld',
              fieldLabel: _translationMap["Classification"],
              width: _fieldRegPopupWidth,
              editable: true,
              valueField: 'code',
              displayField: 'value',
			  value: 'value',
			  code: 'code',
              store: new Ext.data.XmlStore(
                {
                	record: 'Element'
                	,fields: ['code', 'value']
                }),
              getCode : function()
				{
					var rec = this.getSelectedRecord();
					var result = "";
					if (rec) 
						result = rec.data[this.code];
					return result;
				}
            }),
            {
              layout: 'column',
              border: false,
              defaults: {
                layout: 'form',
                border: false
              },
              items: [
                  {
                    columnWidth: 0.5,
                    labelWidth: _labelPopupWidth,
                    items: [new DesktopWeb.Controls.DateField({
                      itemId: 'pStartDateFld',
                      fieldLabel: _translationMap['EffectiveDate'],
                      width: 110,
                      allowBlank: false,
                      format: DesktopWeb.Util
                          .parseSMVDateFormat(DesktopWeb.Util
                              .getDateDisplayFormat())
                    })]
                  },
                  {
                    columnWidth: 0.5,
                    labelWidth: 80,
                    items: [new DesktopWeb.Controls.DateField({
                      itemId: 'pStopDateFld',
                      fieldLabel: _translationMap['StopDate'],
                      allowBlank: false,
                      width: 110,
                      format: DesktopWeb.Util
                          .parseSMVDateFormat(DesktopWeb.Util
                              .getDateDisplayFormat())
                    })]
                  }] // items
            },
            {
              layout: 'column',
              border: false,
              defaults: {
                layout: 'form',
                border: false
              },
              items: [
                  {
                    columnWidth: 0.5,
                    labelWidth: _labelPopupWidth,
                    items: [new DesktopWeb.Controls.SMVComboBox({
                      itemId: 'pStatusFld',
                      fieldLabel: _translationMap["Status"],
                      width: 110,
                      editable: true,
                      allowBlank: false
                    })]
                  },
                  {
                    columnWidth: 0.5,
                    labelWidth: 80,
                    items: [new DesktopWeb.Controls.DateField({
                      itemId: 'pReceiveDateFld',
                      fieldLabel: _translationMap['ReceiptDate'],
                      allowBlank: true,
                      width: 110,
                      format: DesktopWeb.Util
                          .parseSMVDateFormat(DesktopWeb.Util
                              .getDateDisplayFormat())
                    })]
                  }] // items
            }] // items
      }] // items
      ,
      buttons: [
          new DesktopWeb.Controls.ActionButton({
            itemId: 'okBtn',
            text: _translationMap['OK'],
            handler: function() {
              // verify each field of popup
              var isValidPopup =  _controller.isValidPopup(_popups['regulationPopup'].action,'regulationPopup');
            
              if (_popups['regulationPopup'].isValid() && isValidPopup)                 
                _controller.doSave( _popups['regulationPopup'].action,
                    'regulationPopup');
            }
          }), new DesktopWeb.Controls.ActionButton({
            itemId: 'cancelBtn',
            text: _translationMap['Cancel'],
            handler: function() {
              _popups['regulationPopup'].hide();
            }
          })] // buttons
      ,
      init: function(action) {
        this.action = action;
        if (this.action == (_controller.RUNMODE_ADD))
          this.setTitle(_translationMap['RegAgmtMt'] + ' - '
              + _translationMap['Add']);
        else if (action == (_controller.RUNMODE_MOD))
          this.setTitle(_translationMap['RegAgmtMt'] + ' - '
              + _translationMap['Modify']);
      }
    }) // regulationPopup
    ,
    responsibilityPopup: new DesktopWeb.AdvancedControls.PopupWindow({
      width: 420,
      height: 185,
      autoScroll: true,
      action: null,
      closeAction: 'hide',
      title: 'Responsibility - Modify',
      modal: true,
      defaults: {
        border: false
      },
      items: [{
        layout: 'form',
        itemId: 'popup_main2',
        style: 'padding:10px',
        border: false,
        labelWidth: 140,
        items: [new DesktopWeb.Controls.SMVComboBox({
          itemId: 'pResponsibilityFld',
          fieldLabel: _translationMap["Responsibility"],
          width: _fieldResPopupWidth,
          editable: false,
          allowBlank: false
        }), new DesktopWeb.Controls.SMVComboBox({
          itemId: 'pAccountDesignationFld',
          fieldLabel: _translationMap['AccountDesignation'],
          width: _fieldResPopupWidth,
          editable: false,
          allowBlank: false
        }), new DesktopWeb.Controls.SMVComboBox({
          itemId: 'pAccountablePartyFld',
          fieldLabel: _translationMap['AccountableParty'],
          width: _fieldResPopupWidth,
          editable: false,
          allowBlank: false
        })] // items
      }] // items
      ,
      buttons: [
          new DesktopWeb.Controls.ActionButton({
            itemId: 'okBtn',
            text: _translationMap['OK'],
            handler: function() {
              // verify each field of popup              
              if (_popups['responsibilityPopup'].isValid())
                _controller.doSave(_popups['responsibilityPopup'].action,
                    'responsibilityPopup');
            }
          }), new DesktopWeb.Controls.ActionButton({
            itemId: 'cancelBtn',
            text: _translationMap['Cancel'],
            handler: function() {
              _popups['responsibilityPopup'].hide();
            }
          })] // buttons
      ,
      init: function(action) {
        this.action = action;
        this.setTitle(_translationMap["Responsibility"] + ' - '
            + _translationMap['Modify']);
      }
    }) // responsibilityPopup
    ,
    admin: new DesktopWeb.AdvancedControls.PopupWindow({
      width: 395,
      closeAction: 'hide',
      modal: true,
      defaults: {
        border: false
      },
      items: [{
        layout: 'column',
        style: 'padding:4px',
        defaults: {
          border: false,
          labelWidth: 80
        },
        items: [{
          width: 185,
          layout: 'form',
          defaults: {
            width: 80
          },
          items: [new DesktopWeb.Controls.Label({
            itemId: 'userName',
            fieldLabel: _translationMap['Username']
          }), new DesktopWeb.Controls.Label({
            itemId: 'modUser',
            fieldLabel: _translationMap['ModUser']
          })]
        }, {
          width: 185,
          layout: 'form',
          defaults: {
            width: 80
          },
          items: [new DesktopWeb.Controls.Label({
            itemId: 'procDate',
            fieldLabel: _translationMap['ProcessDate']
          }), new DesktopWeb.Controls.Label({
            itemId: 'modDate',
            fieldLabel: _translationMap['ModDate']
          })]
        }]
      }],
      buttons: [new DesktopWeb.Controls.ActionButton({
        text: _translationMap['OK'],
        handler: function() {
          _popups['admin'].hide();
        }
      })],
      init: function(title, data) {
        this.setTitle(title);
        this.getField('procDate').setValue(data['procDate']);
        this.getField('modDate').setValue(data['modDate']);
        this.getField('userName').setValue(data['userName']);
        this.getField('modUser').setValue(data['modUser']);
      }
    }) // admin
    ,
    history: new DesktopWeb.AdvancedControls.HistoryPopup()
  } // _popups

  // PUBLIC ITEMS
  return {
    layoutWidth: _layoutWidth,
    layoutHeight: _layoutHeight,
    fields: _fields,
    grids: _grids,
    buttons: _buttons,
    popups: _popups,
    layout: new Ext.Container({
      width: _layoutWidth,
      height: _layoutHeight,
      items: [
          {
            xtype: 'fieldset',
            title: _translationMap['Search'],
            items: [
                {
                  layout: 'column',
                  labelWidth: 90,
                  items: [{
                    layout: 'form',
                    items: [_fields['regulationSrch']]
                  }]
                },
                {
                  layout: 'column',
                  items: [
                      {
                        width: 280,
                        layout: 'form',
                        labelWidth: 90,
                        items: [_fields['searchForSrch']]
                      },
                      {
                        width: 420,
                        layout: 'form',
                        labelWidth: 90,
                        items: [_fields['searchForAll'],
                            _fields['searchForBroker'],
                            _fields['searchForIntermediary']]
                      }, _buttons['searchBtn']]
                }

            ]
          }
          , _grids['regulationGrid'], {
            xtype: 'fieldset',
            title: _translationMap['Responsibility'],
            items: [_grids['responsibilityGrid']]
          }
        ] // items
    })
    ,
    screenButtons: {
      items: [new DesktopWeb.Controls.ScreenButton({
        text: _translationMap['Close'],
        handler: function() {
          DesktopWeb.Util.cancelScreen();
        }
      })]
    }
  }
}