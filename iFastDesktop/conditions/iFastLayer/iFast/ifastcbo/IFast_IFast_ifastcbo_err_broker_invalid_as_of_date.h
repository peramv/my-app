﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_broker_invalid_as_of_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_broker_invalid_as_of_date() { }
		~CIFast_IFast_ifastcbo_err_broker_invalid_as_of_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_INVALID_AS_OF_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker is inactive as of %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker ist inaktiv mit Wirkung vom %DATE%. Ändern Sie Broker oder Effektivdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El corredor está inactivo al %DATE%. Cambie el corredor o la fecha de entrada en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Courtier inactif en date du %DATE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Makelaar is niet actief vanaf %DATE%. Wijzig de makelaar of de ingangsdatum")); }

        // Actions
	};
}



