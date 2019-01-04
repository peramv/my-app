#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_broker_name_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_broker_name_empty() { }
		~CIFast_IFast_ifastbp_err_broker_name_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NAME_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker name empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Broker name empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Brokername ist nicht eingetragen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Nombre de corredor vacío.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom du courtier est vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaarsnaam is leeg")); }

        // Actions
	};
}



