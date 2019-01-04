#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_virtual_base_method_not_supported : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_virtual_base_method_not_supported() { }
		~CIFast_IFast_dicore_virtual_base_method_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("VIRTUAL_BASE_METHOD_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death notification date must be after or equal to the death date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date de declaration de deces doit être posterieure ou identique a la date de deces.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungs-Datum muss nach dem Todesdatum liegen oder mit diesem übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de notificación de fallecimiento debe ser posterior o igual a la fecha de fallecimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de notification du décès doit être postérieure ou identique à la date de décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datum overlijdensbericht moet later zijn dan of gelijk zijn aan de overlijdensdatum")); }

        // Actions
	};
}



