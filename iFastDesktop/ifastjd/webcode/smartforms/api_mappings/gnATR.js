API.gnATRRequest = {};

API.gnATRRequest = {
	type: 'node'
	,isRequired: function(node){return node.hasData()}
	,description: 'Auto Transfer'
	,repeatCount: 10
	,contents: {			
		ATR: {
			type: 'node'
			,isRequired: function(){return false}
			,contents: {
				accountidtgroup: {
					type: 'node'
					,isRequired: function(){return true}
					,contents: {
						accountIDType: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Account type'
						}
						,accountIDValue: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Account'
						}
					}
				}
				,freqCode: {
					type: 'field'
					,dataType: 'listValue'
					,isRequired: function(){return true}	
					,description: 'Frequency'
					,listName: 'ATRFreqCode'
				}
				,dOfWeek: {
					 type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Day of Week'
					,listName: 'dOfWeek'
				}
				,months: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}						
					,description: 'Monthly Indicator as per Frequency Code'
				}
				,eom: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'End of Month Flag'
				}
				,BackendloadFee: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Back end load fee yes/no'
				}
				,effDate: {
					type: 'field'
					,dataType: 'date'					
					,isRequired: function(){return true}
					,description: 'Effective Date'
				}
				,FundInfo: {
					type: 'node'
					,isRequired: function(){return true}					
					,contents: {
						fundIDType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'Fund Id type'
						}
						,fundIDDesc: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'Fund Identifier'
						}
						,fundIDValue: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Fund Id Value'
						}
						,amtType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Amount type'
						}
						,amount: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Amount'
						}
					}
				}
				,StopDate: {
					type: 'field'
					,dataType: 'date'
					,isRequired: function(){return false}
					,description: 'Auto Transfer Stop Date'
				}
				,Allocations: {
					type: 'node'
					,isRequired: function(){return true}
					,contents: {
						Allocation: {
							type: 'node'
							,isRequired: function(){return false}
							,description: 'Allocation'
							,contents: {
								FundInfo: {
									type: 'node'
									,isRequired: function(){return true}
									,contents: {
										fundIDType: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return true}				
											,description: 'The type of ID that you are submitting to locate the fund'
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
											,isRequired: function(){return true}				
											,description: 'The value being used to locate the fund'
										}
										,amtType: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return true}				
											,description: 'Amount Type'
										}
										,amount: {
											type: 'field'						
											,dataType: 'string'
											,isRequired: function(){return true}				
											,description: 'Amount'
										}
									}
								}
								,accountIDType: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return false}	
									,description: ''
								}
								,accountIDValue: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return false}	
									,description: 'Account'
								}
							}
						}
					}
				}
				,Fee: {
					type: 'node'
					,isRequired: function(){return false}
					,description: 'Fee'		
					,contents: {
						FeeType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'type of fee'
						}
						,AmtType: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return true}				
							,description: 'amount type'
						}
						,FeeAmount: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'amount'
						}
						,Currency: {
							type: 'field'						
							,dataType: 'string'
							,isRequired: function(){return false}				
							,description: 'currency for the fee'
						}
					}
				}
				,StopDate: {
					type: 'field'
					,dataType: 'date'
					,isRequired: function(){return false}		
					,description: 'Stop Date to be applied to the ATR request'
				}
			}
		}
		,TEMP: {
			type: 'node'
			,isRequired: function(node){return false}		
			,contents: {
				semiMonthlyDate: {
					type: 'field'
					,dataType: 'date'
					,isRequired: function(){return false}
					,description: 'Effective Date'				
				}
			}
		}
	}
};

