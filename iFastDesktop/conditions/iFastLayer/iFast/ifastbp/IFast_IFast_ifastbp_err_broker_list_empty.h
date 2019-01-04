#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_broker_list_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_broker_list_empty() { }
		~CIFast_IFast_ifastbp_err_broker_list_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_LIST_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker list empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Broker list empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Brokerliste ist nicht eingetragen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Lista de corredores vacía.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La liste du courtier est vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaarslijst is leeg")); }

        // Actions
	};
}



