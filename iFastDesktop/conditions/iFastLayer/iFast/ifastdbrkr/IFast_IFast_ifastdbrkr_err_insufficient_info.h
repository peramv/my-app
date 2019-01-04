#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_insufficient_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_insufficient_info() { }
		~CIFast_IFast_ifastdbrkr_err_insufficient_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUFFICIENT_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient (or Blank) address information for a match.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Insufficient (or Blank) address information for a match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unzureichende (oder leere) Adressinformation für eine Entsprechung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Información de dirección insuficiente (o en blanco) para una comparación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information sur l'adresse manquante ou insuffisante pour obtenir une correspondance")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onvolledige (of lege) adresgegevens voor een overeenstemming")); }

        // Actions
	};
}



