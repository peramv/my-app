#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_logon_no_error : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_logon_no_error() { }
		~CIFast_IFast_diawdi_diawdi_logon_no_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_NO_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death date must be after or equal to the birth date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date de deces doit être posterieure ou identique a la date de naissance.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesdatum muss nach dem Geburtsdatum liegen oder mit diesem übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de fallecimiento debe ser posterior o igual a la fecha de nacimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de décès doit être postérieure ou identique à la date de naissance.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overlijdensdatum moet later zijn dan of gelijk zijn aan de geboortedatum")); }

        // Actions
	};
}



