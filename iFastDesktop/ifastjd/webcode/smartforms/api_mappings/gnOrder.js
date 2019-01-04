API.gnOrderRequest = {};

API.gnOrderRequest = {
	type: 'node'
	,isRequired: function(node){return node.hasData()}
	,description: 'Order'
	,repeatCount: 8
	,contents: {
		Order: {
			type: 'node'
			,isRequired: function(){return true}
			,contents: {
				actionCode: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return true}
					,description: 'Action'					
				}
				,senderRefNum: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Unique reference of the order'
				}
				,transactionType: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Transaction Type'					
				}
				,trxnTyp: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Transaction type'
					,listName: 'trxnTyp'
				}
				,trxnTypDtl: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}					
					,description: 'Identifies the specific type of order transaction'
				}
				,accountIDType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Type of indicator used to identify the account'
				}
				,accountIDValue: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Account identifier'
				}
				,fundIDDesc: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(node){return false}				
					,description: 'Fund identifier'
				}					
				,fundIDType: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(node){return false}				
					,description: 'Type of fund identifier'
				}				
				,fundIDValue: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Fund identifier'
				}				
				,tradeDate: {
					type: 'field'						
					,dataType: 'date'
					,isRequired: function(){return false}			
					,description: 'Trade date'
				}
				,orderType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Order type'
					,listName: 'orderType'
				}
				,wireOrdNum: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}			
					,description: 'Wire order number'
				}
				,grossNetIndicator: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Identifies gross or net amount'
				}
				,amountType: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Amount type'
					,listName: 'amountType'
				}
				,amount: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return true}				
					,description: 'Amount'
				}
				,settleCurrency: {
					type: 'field'						
					,dataType: 'listValue'
					,isRequired: function(){return false}				
					,description: 'Currency'
					,listName: 'Curr'
				}
				,clientComm: {
					type: 'field'						
					,dataType: 'string'
					,isRequired: function(){return false}				
					,description: 'Commission'
				}									
				,allocDtl: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}
					,contents: {
						Allocation: {
							type: 'node'
							,isRequired: function(node){return node.hasData()}
							,description: 'Allocation'
							,repeatCount: 8
							,contents: {
								fundIDType: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Type of fund identifier'
								}								
								,fundIDValue: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'fund identifier'
								}
								,fundIDDesc: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(node){return false}				
									,description: 'Fund identifier'
								}		
								,amountType: {
									type: 'field'						
									,dataType: 'listValue'
									,isRequired: function(){return true}				
									,description: 'Amount Type'
									,listName: 'allocAmtType'
								}
								,amount: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return true}				
									,description: 'Amount'
								}
								,clientComm: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return false}				
									,description: 'Client-paid commission'
								}
								,certInd: {
									type: 'field'						
									,dataType: 'string'
									,isRequired: function(){return false}				
									,description: 'Certificate indicatior'
								}
							}
						}
					}
				}
				,trfOutInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						accountIDType: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Type of indicator used to identify the account'
						},
						accountIDValue: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Account identifier'
						}
					}
				}
				,ExchOutInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						fundIDType: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Type of fund identifier'
						}
						,fundIDValue: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Fund identifier'
						}
					}
				}
				,cntbWdCode: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'identifies the type of contribution or withdrawal'
				}
				,sourceOfFund: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Source/Desitnation of funds'
				}
				,payType: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Pay type'
				}
				,Payment: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						ChequeInfo: {
							type: 'node'
							,isRequired: function(){return false}
							,contents: {
								payee: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Payee information'
								}
								,Name: {
									type: 'node'
									,isRequired: function(){return true}
									,contents: {
										orgName: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Organization name'
										}
										,titleCode: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Salutation'
										}
										,lastName: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Last Name'
										}
										,firstName: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'First Name'
										}
									}
								}
								,Address: {
									type: 'node'
									,status: 'conditional'
									,contents: {
										addressLn1: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Address line 1'
										}
										,addressLn2: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Address line 2'
										}
										,addressLn3: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Address line 3'
										}
										,city: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'City'
										}
										,provState: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Province or State'
										}
										,country: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return true}
											,description: 'Country code'
										}
										,postalZip: {
											type: 'field'
											,dataType: 'string'
											,isRequired: function(){return false}
											,description: 'Postal Code'
										}
									}
								}
							}
						}
						,BkInfo: {
							type: 'node'
							,isRequired: function(){return false}
							,contents: {
								instutNum: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Institution code (bank type  Canadian)'
								}
								,branchNum: {
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
								,currency: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Currency'
								}
								,holder: {
									type: 'field'
									,dataType: 'string'
									,isRequired: function(){return true}
									,description: 'Bank account owner name'
								}		
							}
						}
					}
				}
				,OverrideTax: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						fedRatePUD: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Federal tax amount type'
						}
						,fedRate: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Federal tax'
						}
						,provRatePUD: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Provincial tax amount type'
						}
						,provRatePUD: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Provincial tax'
						}		
					}
				}
				,taxEvent: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Indicates if the transfer is at cost or at market value'
				}
				,SegInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						matureDate:{
							type: 'field'
							,dataType: 'date'
							,isRequired: function(){return false}
							,description: 'Maturity Date'
						}
						,jurProv: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Province of Jurisdiction'
						}
					}
				}
				,settlStat: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Settlement Status'
				}
				,settlSrc: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Party responsible to settle the order'
				}				
				,contribPeriod: {
					type: 'field'
					,dataType: 'string'
					,isRequired: function(){return false}
					,description: 'Contribution Period'
				}
				,Remarks: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						line1: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return true}
							,description: 'Remarks line 1'
						}
						,line2: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Remarks line 2'
						}
						,line3: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Remarks line 3'
						}
					}
				}
				,AddlInfo: {
					type: 'node'
					,isRequired: function(){return false}
					,contents: {
						addlName: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Additional Name'
						}
						,addlValue: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Additional Value'
						}
					}
				}
				,OrderExt: {
					type: 'node'
					,isRequired: function(node){return node.hasData()}
					,contents: {
						supprCode: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Suppression Code'
						}
						,batchRef: {
							type: 'field'
							,dataType: 'string'
							,isRequired: function(){return false}
							,description: 'Batch number'
						}	
						,depType: {
							type: 'field'						
							,dataType: 'listValue'
							,isRequired: function(){return false}				
							,description: 'Dep. type'
							,listName: 'OrderDepType'
						}
						,depDate: {
							type: 'field'						
							,dataType: 'date'
							,isRequired: function(){return false}				
							,description: 'Deposit date'					
						}
						,accCode: {
							type: 'field'
							,dataType: 'listValue'
							,isRequired: function(){return false}
							,description: 'Accountability code'
							,listName: 'AccCode'
						}				
						,rsnCode: {
							type: 'field'
							,dataType: 'listValue'
							,isRequired: function(){return false}
							,description: 'Reason code'
							,listName: 'RsnCode'
						}		
					}
				}
			}
		}
	}	
};
