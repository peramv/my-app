#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_intermediary_address_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_intermediary_address_not_found() { }
		~CIFast_IFast_ifastcbo_err_broker_intermediary_address_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker/Intermediary code not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Broker/Intermediary code not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker/Mittler (Intermediary)-Code nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el código de corredor/intermediario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de courtier/d'intermédiaire introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Code makelaar/tussenpersoon is niet gevonden")); }

        // Actions
	};
}



