#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_field_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_field_empty() { }
		~CIFast_IFast_ditabuscore_err_field_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date in previous tax year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Trade date in previous tax year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handelsdatum in vorigem Steuerjahr")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de transacción en año fiscal anterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction est située dans l'année d'imposition précédente.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelsdatum ligt in voorgaand belastingjaar")); }

        // Actions
	};
}



