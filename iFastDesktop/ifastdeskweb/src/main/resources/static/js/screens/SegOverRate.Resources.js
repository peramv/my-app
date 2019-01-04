/*********************************************************************************************
 * @file	SegOverRate.Resources.js
 * @author	Matira Thanetkulabut
 * @desc	Resources file for Override screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Contract Information > Override Screen
 *  
 *  History : 
 *  
 *  28-Sep-2016 Matira Thanetkulabut P0256533 T84091 MSF - Desktop
 *              - Initial
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    // content dimensions
    var _layoutHeight = 200;
    var _layoutWidth  = 400;

    // **** fields **** 
    var _fields = {
    }
    
    // **** buttons ****
	var _buttons = {
    }
    
    // **** grids ****
	var _grids = {
        guarOver: new Ext.grid.EditorGridPanel(
        {
            height: 200
            ,autoScroll: true
            ,autoExpandColumn: 'guarType'
            ,clicksToEdit: 1
            ,store: new Ext.data.XmlStore(
            {
                record: 'SEGOvrRate'
                ,fields: ['guarType', 'guarTypeCode', 'guarRate', 'overridden', 'enableOvrRate', 'defaultRate', 'userName', 'processedDate', 'modUser', 'modDate', 'ApplRates',
				        'myrates']
				,listeners: {
                    load: function (store, records) {
                        Ext.each(records, function (record) {
							record.data.myrates = _controller.getApplRate(record.data.guarType);
                        });
                        store.fireEvent('datachanged', store); //to set data in grid again
                        
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: { menuDisabled: true }
                
                ,columns: [
                {
                    header: _translationMap['GuaranteeType']
                    ,id: 'guarType'
                    ,width: 100
                    ,dataIndex: 'guarType'
                }
                ,{
                    header: _translationMap['Rate']
                    ,width: 80
                    ,dataIndex: 'guarRate'
					,renderer: function(val, metaData, record, row, col, store, gridView){
						this.editor.loadData(record.data.myrates);
                        this.editor.setDisabled(!_controller.isEnabled(record.data.guarType));
						return val;
					}
                  
					,editor: new DesktopWeb.Controls.ComboBox({
                        lazyInit: false,
                        editable: false,
                        store: new Ext.data.ArrayStore({
                            fields: ['rate']
                        }),
                        valueField: 'rate',
                        displayField: 'rate',
                        listeners: {
                            focus: function (comboField) {
                                comboField.doQuery(comboField.allQuery, true);
                                comboField.expand();
                            }
                            ,select: function (comboField, record, index) {
                                comboField.fireEvent('blur');
                            }
                            ,change: function(fld, newValue, oldValue ){
                                if(newValue != oldValue){
                                    _controller.updatesFlag = true;
                                }
                            }
                    }
                    })
				}
                ,{
                    header: _translationMap['Overridden']
                    ,width: 70
                    ,dataIndex: 'overridden' 
                }]
            })
        })
    }
    
    // **** popups ****
    var _popups = {
        admin: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 400
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
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'userName'
                            ,fieldLabel: _translationMap['Username']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'modUser'
                            ,fieldLabel: _translationMap['ModUser']
                        })
                    ]
                }
                ,{
                    width: 185
                    ,layout: 'form'
                    ,defaults: {width: 80}
                    ,items: 
                    [
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'procDate'
                            ,fieldLabel: _translationMap['ProcessDate']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'modDate'
                            ,fieldLabel: _translationMap['ModDate']
                        })
                    ]
                }]
            }]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['OK']
                    ,handler: function()
                    {
                        _popups['admin'].hide();
                    }
                })
            ]
            ,init: function(title, data)
            {
                this.setTitle(title);
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);
            }
        })
    }
    
     // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight

        ,fields: _fields

        ,grids: _grids

        ,popups: _popups

        ,buttons: _buttons

        ,layout: new Ext.Container(
        {
            height: _layoutHeight
            ,width: _layoutWidth
            ,items: [_grids['guarOver']]
        })
        
        ,screenButtons: [
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['OK']
                ,id: "okBtn1"
                ,handler: function(){
                    if(_controller.updatesFlag){
                        DesktopWeb.Util.commitScreen();
                    }else{
                        DesktopWeb.Util.cancelScreen();
                    }
                }
            })
            ,new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Cancel']
                ,handler: function(){
                    if (_controller.updatesFlag){
                        DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
                    }else{
                        cancelScreen(true);
                    }
                    function cancelScreen(confirm){
                        if (confirm) 
                            DesktopWeb.Util.cancelScreen();
                    }
                }
            })
            ,new DesktopWeb.Controls.ScreenButton({
                itemId: 'adminBtn'
                ,text: _translationMap['Admin'] + "/" + _translationMap['Dates']
                ,handler: function(){
                    _controller.openAdminPopup();
                }
            })
        ]
    }
}

