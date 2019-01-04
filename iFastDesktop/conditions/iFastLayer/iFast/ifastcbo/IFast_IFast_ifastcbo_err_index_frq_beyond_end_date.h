#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_index_frq_beyond_end_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_index_frq_beyond_end_date() { }
		~CIFast_IFast_ifastcbo_err_index_frq_beyond_end_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INDEX_FRQ_BEYOND_END_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index frequency must not go beyond the End Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Index-Häufigkeit darf nicht über das Enddatum hinausreichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La frecuencia del índice no debe superar la fecha de terminación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La fréquence d'indexation ne doit pas aller au-delà de la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexfrequentie moet niet over de einddatum gaan")); }

        // Actions
	};
}



