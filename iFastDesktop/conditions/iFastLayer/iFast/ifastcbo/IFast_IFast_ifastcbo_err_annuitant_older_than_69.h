#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_older_than_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_older_than_69() { }
		~CIFast_IFast_ifastcbo_err_annuitant_older_than_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_OLDER_THAN_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant is older than 71.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rentenempfänger ist älter als 71.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El titular de la anualidad tiene más de 71 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le crédirentier est âgé de plus de 71 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Lijfrentetrekker is ouder dan 71")); }

        // Actions
	};
}



