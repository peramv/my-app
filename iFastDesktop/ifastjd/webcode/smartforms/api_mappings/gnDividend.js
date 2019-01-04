API.gnDividendRequest = {};

API.gnDividendRequest = {
	type: 'node'
	,repeatCount: 10
	,isRequired: function(node){return node.hasData()}
	,description: 'Dividend'
	,contents: {			
		Dividend: {
			type: 'node'
			,isRequired: function(node){return node.hasData()}
			,contents: {
				transType: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Type of Distribution'
				}
				,accountidtgroup:{
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						accountIDType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Account'
						}
						,accountIDValue: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Account'
						}	
					}
				}
				,effDate: {
					type: 'field'
					,dataType: 'date'
					,isRequired: function(){return true}
					,description: 'Effective Date'
				}
				,fundIDDesc: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'Fund Identifier'
				}
				,fundIDType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Fund Id Type'
						}
				,fundIDValue: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Fund Identifier'
				}					
				,FundListTo: {
					type: 'node'
					,isRequired: function(){return true}
					,contents: {
						FundInfo: {
							type: 'node'
							,isRequired: function(){return true}
							,contents: {
								fundIDType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Fund Id type'
								}
								,fundIDDesc: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return false}				
									,description: 'Fund Identifier'
								}
								,fundIDValue: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return false}
									,description: 'Fund Identifier'
								}
								,amtType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Type of Amount'
								}
								,amount: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Amount'
								}
							}
						}
					}
				}
				,payType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Payment Type'
					,listName: 'DivPayType'
				}
				,adCd: {
					type: 'field'						
					,dataType: 'string'
					,status: 'conditional'				
					,description: 'Address Code for the Dividend Cheque'
				}
				,BkInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						instCode: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Institution code'
						}
						,transitNo: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Transit number'
						}
						,bkAcctType: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Bank account type'
						}
						,bkAcctNum: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Bank account number'
						}
						,holder: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Bank Account holder'
						}
						,currency: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Currency'
						}		
					}
				}
			}
		}
	}
};
