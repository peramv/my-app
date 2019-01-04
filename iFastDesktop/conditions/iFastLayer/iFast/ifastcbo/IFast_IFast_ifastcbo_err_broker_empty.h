#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_empty() { }
		~CIFast_IFast_ifastcbo_err_broker_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Courtier doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El corredor no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Courtier doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar kan niet leeg zijn")); }

        // Actions
	};
}



