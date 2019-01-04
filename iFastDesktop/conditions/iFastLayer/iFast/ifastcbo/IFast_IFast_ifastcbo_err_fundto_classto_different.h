#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundto_classto_different : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundto_classto_different() { }
		~CIFast_IFast_ifastcbo_err_fundto_classto_different() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDTO_CLASSTO_DIFFERENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Investing to a different fund is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Investieren in einen anderen Fonds ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite invertir en otro fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Investissement dans un fonds différent non autorisé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beleggen naar een ander fonds is niet toegestaan")); }

        // Actions
	};
}



