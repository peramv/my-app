#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_new_split_period_overlaps : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_new_split_period_overlaps() { }
		~CIFast_IFast_ifastcbo_err_new_split_period_overlaps() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEW_SPLIT_PERIOD_OVERLAPS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New split period overlaps with other split periods.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Neue Split-Periode überschneidet sich mit anderen Split-Perioden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El nuevo período dividido se superpone con otros períodos divididos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La nouvelle période de partage chevauche les autres périodes de partage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nieuwe gesplitste periode overlapt met andere gesplitste periodes")); }

        // Actions
	};
}



