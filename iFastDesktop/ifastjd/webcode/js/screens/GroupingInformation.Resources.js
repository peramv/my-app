/*********************************************************************************************
 * @file    GroupingInformation.Resources.js
 * @author    Aurkarn Mongkonrat
 * @desc    Resources JS file for Grouping Information screen
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    // content dimensions
    var _layoutHeight = 440;
    var _layoutWidth = 660;
    
    var _buttons = {
        acctSearchBtn: new DesktopWeb.Controls.ActionButton({                                                                                        
            text: _translationMap['SearchBtn']
            ,handler: function(){
                _controller.doGroupingSearch(_fields['account'].getValue());
            }
        })
    }
    
    // **** fields ****
    var _fields = {        
        account: new DesktopWeb.Controls.SuggestField({
            fieldLabel: _translationMap['Account']
            ,smartview: 'accountSearch'                
            ,fields: ['displayValue', 'acctNum']                        
            ,valueField: 'acctNum'                                
            ,width: 370                                                        
        })
        ,benefOwnerName: new DesktopWeb.Controls.Label({
            width: 380
            ,fieldLabel: _translationMap['BenefOwnerName']
        })
    }
    
    // **** grids ****
    var _grids = {
        acctGroupGrid: new DesktopWeb.AdvancedControls.GridPanel({
            autoScroll: true                            
            ,height: 180
            ,title: _translationMap['AccountGroupTitle']
            ,store: new Ext.data.XmlStore({
                record: 'LnkAcct'
                ,fields: ['groupID'
                          ,'groupDescription' 
						  ,'groupType'
						  ,'groupTypeDesc'
                          ,'groupStatus'
                          ,'primaryAcct'
                          ,'deff'
                          ,'stopDate']
                ,listeners: {
                    load: function(store, records)
                    {
                        Ext.each(records, function(record){
                            record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
                            record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
                        });
                        
                        store.fireEvent('datachanged', store);
                    }
                }
            })
            ,selModel: new Ext.grid.RowSelectionModel({
                singleSelect: true
            })
            ,colModel: new Ext.grid.ColumnModel({
                defaults: {
                    menuDisabled: true
                }
                ,columns: [        
                     {header: _translationMap['GroupID'], dataIndex: 'groupID', width: 65}
                    ,{header: _translationMap['GroupDescription'], dataIndex: 'groupDescription', width: 160}
					,{header: _translationMap['GroupType'], dataIndex: 'groupTypeDesc', width: 110}
                    ,{header: _translationMap['AcctGroupStatus'], dataIndex: 'groupStatus', width:95}
                    ,{header: _translationMap['Primary'], dataIndex: 'primaryAcct', width:50}
                    ,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:80}
                    ,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width:70}
                ]
            })    
        })
        ,feeModelGrid: new DesktopWeb.AdvancedControls.GridPanel({
            autoScroll: true                            
            ,height: 180
            ,title: _translationMap['FeeModelTitle']
            ,store: new Ext.data.XmlStore({
                record: 'AcctFeeModelDetl'
                ,fields: ['feeModelCode'
                          ,'feeModelDesc' 
						  ,'feeModelTypeDesc'
                          ,'effectiveDate'
                          ,'stopDate']
                ,listeners: {
                    load: function(store, records)
                    {
                        Ext.each(records, function(record){
                            record.data.effectiveDate = DesktopWeb.Util.getDateDisplayValue(record.data.effectiveDate);
                            record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
                        });
                        
                        store.fireEvent('datachanged', store);
                    }
                }
            })
            ,selModel: new Ext.grid.RowSelectionModel({
                singleSelect: true
            })
            ,colModel: new Ext.grid.ColumnModel({
                defaults: {
                    menuDisabled: true
                }
                ,columns: [                                                    
                     {header: _translationMap['FeeModelCode'], dataIndex: 'feeModelCode', width: 90}
                    ,{header: _translationMap['FeeModelDesc'], dataIndex: 'feeModelDesc', width:230}
					,{header: _translationMap['FeeModelType'], dataIndex: 'feeModelTypeDesc', width:130}
                    ,{header: _translationMap['EffectiveDate'], dataIndex: 'effectiveDate', width:90}
                    ,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width:90}
                ]
            })
        })
    }
    
    // **** popups ****
    var _popups = {                    
    } 
    
    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth
        
        ,layoutHeight: _layoutHeight
        
        ,fields: _fields
        
        ,grids: _grids
        
        ,popups: _popups
        
        ,buttons: _buttons
        
        ,layout: new Ext.Container({
            height: _layoutHeight
            ,width: _layoutWidth
            ,items: [
                {
                    layout: 'column'
                    ,defaults: {
                        layout: 'form'
                    }
                    ,items: [
                        {
                            width: 490
                            ,labelWidth: 100
                            ,items: [
                                _fields['account']
                            ]
                        }
                        ,{
                            width: 60
                            ,items: [
                                _buttons['acctSearchBtn']
                            ]
                        }
                    ]
                }
                ,{
                    layout: 'column'
                    ,defaults: {
                        layout: 'form'
                    }
                    ,items: [
                        {
                            width: 490
                            ,labelWidth: 100
                            ,items: [
                                _fields['benefOwnerName']
                            ]
                        }
                    ]
                }
                ,_grids['acctGroupGrid']
                ,{}
                ,_grids['feeModelGrid']
            ]                                                                                
        })
        ,screenButtons: [                        
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Close']
                ,handler: function(){DesktopWeb.Util.cancelScreen()}
            })
        ]            
    }
}