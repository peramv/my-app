/*********************************************************************************************
 * @file	NotionalBalance.Resources.js
 * @author	Suvacin Thatchanallur Vijayaraghavan
 * @desc	Resources JS file for NotionalBalance.
 *********************************************************************************************/
DesktopWeb.ScreenResources = function(ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _layoutHeight = 650;
	var _layoutWidth = 750;

	// **** fields ****
	var _fields = {
		beneficaryName : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['BeneficaryName'],
			style : 'padding-left:5px;',
			width : 200
		}),		
        period: new DesktopWeb.Controls.ComboBox({
            fieldLabel: _translationMap["Period"],
            width: 100,
            disabled: false,
            valueField: 'code',
            displayField: 'value',
            allowBlank: false,
            store: new Ext.data.XmlStore({
                record: 'elements',
                fields: ['code', 'value']
            })
        }),
        periodRadio: new DesktopWeb.Controls.Radio({
            name: 'filter',
            listeners: {
                check: function () {
                    _controller.toggleFilterFields();
                }
            }
        }),
        asOfDate: new DesktopWeb.Controls.DateField({
            fieldLabel: _translationMap["AsOf"],
            disabled: true,
            format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()),
            validator : function(value){
				var validate=_controller.validateAsOfDate(value);
				//_controller.enableOKButtonPopUp(validate);
				return validate;
		    }
        }),
        asOfRadio: new DesktopWeb.Controls.Radio({
            name: 'filter',
            listeners: {
                check: function () {
                    _controller.toggleFilterFields();
                }
            }
        }),                
		marketValue : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['MarketValue'],
			style : 'padding-left:5px;',
			width : 100
		}),
		jan1FMV : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['Jan1FMV'],
			style : 'padding-left:5px;',
			width : 100
		}),
		aha : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['AHA'],
			style : 'padding-left:5px;',
			width : 100
		}),
		ldapMaximum : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['LDAPMaximum'],
			style : 'padding-left:5px;',
			width : 100
		}),
		taxableRedemptions : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['TaxableRedemptions'],
			style : 'padding-left:5px;',
			width : 100
		}), 
		sdspMaximum :  new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['SDSPMaximum'],
			style : 'padding-left:5px;',
			width : 100
		}),
		pgap : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['PGAP'],
			style : 'padding-left:5px;',
			width : 100
		}),
		pgapMaximum : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['PGAPMaximum'],
			style : 'padding-left:5px;',
			width : 100
		})
	}
	
	var _grids = {
		contributionCategory : new DesktopWeb.AdvancedControls.GridPanel({
			width: 743,
			height: 156,
			store: new Ext.data.XmlStore(
				{
					record: 'contributions'
					,fields: [
						'contCategory','purchases', 'redemptions', 'contBalance'
					]
				}
			)
		
			,selModel: new Ext.grid.RowSelectionModel(
				{
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.enableButtons(record);
							}
						}
					}
				}
			)
			,viewConfig: { autoFill: true }
		
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				},
				columns:[
		            {header: _translationMap['CatTitle'], dataIndex: 'contCategory', width: 330, renderer: _controller.addHyperLinkContrib},
		            {header: _translationMap['Purchases'], dataIndex: 'purchases', width: 120, align: "right", renderer : _controller.numberRenderer},
		            {header: _translationMap['Redemptions'], dataIndex: 'redemptions', width: 120, align: "right", renderer : _controller.numberRenderer},
		            {header: _translationMap['ContBalance'], dataIndex: 'contBalance', width: 120, align: "right", innerCls:"grid-last-cell", renderer : _controller.numberRenderer}
		        ]
			})
		}),
		
		grantBondCategory : new DesktopWeb.AdvancedControls.GridPanel({
			width: 745,
			height: 68,
			store: new Ext.data.XmlStore(
				{
					record: 'grantsBonds'
					,fields: [
						'category','received', 'paidOut', 'repayment', 'balance'
					]
		
				}
			)
		
			,selModel: new Ext.grid.RowSelectionModel(
				{
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.enableButtons(record);
							}
						}
					}
				}
			)
			,viewConfig: { autoFill: true }
		
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}

				,columns: [
					{header: _translationMap['CatTitle'], id:'category', dataIndex: 'category',width: 250, renderer: _controller.addHyperLink},
					{header: _translationMap['Received'], id:'received', dataIndex: 'received',width: 130, align: "right", renderer : _controller.numberRenderer},
					{header: _translationMap['PaidOut'], id:'paidOut', dataIndex: 'paidOut',width: 130, align: "right", renderer : _controller.numberRenderer},
					{header: _translationMap['Repayment'], id:'repayment', dataIndex: 'repayment',width: 110, align: "right", renderer : _controller.numberRenderer},
					{header: _translationMap['Balance'], id:'balance', dataIndex: 'balance',width: 100, align: "right", renderer : _controller.numberRenderer}
					
				]
			})

		,clearGridData: function()
		{
			
		}
		}),
		limitsHd: new DesktopWeb.AdvancedControls.GridPanel({
			height: 22
            ,enableHdMenu: false
            ,enableColumnMove: false
            ,store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['Limits'], width: 60, fixed: true},
                {header: _translationMap['Contributions'], width: 219, align: "center"},
                {header: _translationMap['Grants'], width: 219, align: "center"},
                {header: _translationMap['Bonds'], width: 219, align: "center"}
            ]
        }),
		limitsDetailHd: new DesktopWeb.AdvancedControls.GridPanel({
			height: 22
            ,enableHdMenu: false
            ,enableColumnMove: false
            ,store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['LimitsBlank'], width: 60, fixed: true},
                {header: _translationMap['Maximum'], width: 73, align: "center"},
                {header: _translationMap['Used'], width: 73, align: "center"},
                {header: _translationMap['Remaining'], width: 73, align: "center"},
                {header: _translationMap['Maximum'], width: 73, align: "center"},
                {header: _translationMap['Used'], width: 73, align: "center"},
                {header: _translationMap['Remaining'], width: 73, align: "center"},
                {header: _translationMap['Maximum'], width: 73, align: "center"},
                {header: _translationMap['Used'], width: 73, align: "center"},
                {header: _translationMap['Remaining'], width: 73, align: "center"}
            ]
        }),
        limitsDetail: new DesktopWeb.AdvancedControls.GridPanel({
            height: 50,
            enableHdMenu: false,
            enableColumnMove: false,            
            hideHeaders: true,
            store: new Ext.data.XmlStore(
					{
						record: 'limits'
						,fields: [
							'limitCat','contMax', 'contUsed', 'contRemaining', 'grantsMax', 'grantsUsed', 'grantsRemaining', 'bondsMax', 'bondsUsed', 'bondsRemaining'
						]
			
					}
				),            
            columns:[
                {header: _translationMap['Limits'], dataIndex: 'limitCat', width: 60, fixed: true},
                /*{header: _translationMap['Maximum'], dataIndex: 'contMax', width: 73, align: "right", filter : {type: 'numeric'}, renderer: function(value){
                	return Ext.util.Format.number(value, '0,000.00'); 
                }},*/
                {header: _translationMap['Maximum'], dataIndex: 'contMax', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Used'], dataIndex: 'contUsed', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Remaining'], dataIndex: 'contRemaining', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Maximum'], dataIndex: 'grantsMax', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Used'], dataIndex: 'grantsUsed', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Remaining'], dataIndex: 'grantsRemaining', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Maximum'], dataIndex: 'bondsMax', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Used'], dataIndex: 'bondsUsed', width: 73, align: "right", renderer : _controller.numberRenderer},
                {header: _translationMap['Remaining'], dataIndex: 'bondsRemaining', width: 73, align: "right", renderer : _controller.numberRenderer}
            ]
        })  
		
	}
	
    // **** buttons ****
    var _buttons = {
        refreshBtn: new DesktopWeb.Controls.ActionButton({
            text: _translationMap["Refresh"],
            style: 'margin-left: 50px;',
            listeners: {
                click: function () {
                    _controller.refresh();
                }
            }
        })
    }	

	return {
		layoutWidth : _layoutWidth,
		layoutHeight : _layoutHeight,
		fields : _fields,
		grids: _grids,
		layout : new Ext.Container(
				{
					height : _layoutHeight,
					width : _layoutWidth,
					items:[
						{
							layout : 'form',
							items: [_fields['beneficaryName']]
						},
						{                        
		                    layout: 'column',
		                    items: [
		                        {
		                        	columnWidth: 0.05,
		                            items: [_fields['periodRadio']]
		                            
		                        },
		                        {
		                        	layout : 'form',
		                        	items:[_fields['period']],
		                        	columnWidth: 0.35
		                           
		                        },
		                        {
		                        	columnWidth: 0.05,
		                            items: [_fields['asOfRadio']]
		                            
		                        },
		                        {
		                        	layout : 'form',
		                        	columnWidth: 0.35,
		                        	items:[_fields['asOfDate']]
		                            
		                        },
		                        {
		                        	layout : 'form',
		                        	columnWidth: 0.2,
		                        	items: [_buttons['refreshBtn']]
		                        }
		                    ]
		                },
						{
						layout : 'form',
						items:[
						{
		                    layout: 'form',
		                    items: [
		                    	{
		                    		xtype: 'fieldset',
		                            title: _translationMap['ContCategory'],
		                            items: [
		                                {
		                                    layout: 'form',
		                                    items: [
		                                        _grids['contributionCategory']
		                                    ]
		                                }
		                            ]
		                    	},
		                    	{
		                    		xtype: 'fieldset',
		                            title: _translationMap['Category'],
		                            items: [
		                                {
		                                    layout: 'form',
		                                    items: [
		                                        _grids['grantBondCategory']
		                                    ]
		                                }
		                            ]
		                    	},
		                        {
		                        	xtype : 'fieldset',
		    						items : [ {
		    							layout : 'column',
		    							labelWidth : 220,
		    							items : [
		    									{
		    										columnWidth : 0.50,
		    										layout : 'form',
		    										items : [
		    												_fields['marketValue'],
		    												_fields['aha'],
		    												_fields['taxableRedemptions'],
		    												_fields['sdspMaximum']]
		    												
		    									},
		    									{
		    										columnWidth : 0.50,
		    										layout : 'form',
		    										items : [
		    												_fields['jan1FMV'],
		    												_fields['ldapMaximum'],
		    												_fields['pgap'],
		    												_fields['pgapMaximum']]
		    									} ]
		    						} ]
		                        },
		                        {
		                        	xtype: 'fieldset',
		                            title: _translationMap['Limits'],
		                            items: [
		                                {
		                                    layout: 'form',
		                                    items: [
		                                        _grids['limitsHd'],
		                                        _grids['limitsDetailHd'],
		                                        _grids['limitsDetail']
		                                    ]
		                                }
		                            ]
		                        }
		                    ]
		                }						
						]
					}]
				}),
		screenButtons : {
			items : [ new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Activity'],
				handler: function() {
					_controller.clickHandle_ActivityBtn();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['BtnCancel'],
	            handler: function () {
	                DesktopWeb.Util.cancelScreen();
	            }
			}) ]
		}
	}
}
