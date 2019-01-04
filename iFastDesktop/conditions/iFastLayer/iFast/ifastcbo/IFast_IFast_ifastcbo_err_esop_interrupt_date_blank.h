#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_esop_interrupt_date_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_esop_interrupt_date_blank() { }
		~CIFast_IFast_ifastcbo_err_esop_interrupt_date_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESOP_INTERRUPT_DATE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Interrupt date cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unterbrechungsdatum darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de interrupción no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'interruption est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onderbrekingsdatum kan niet leeg zijn")); }

        // Actions
	};
}



