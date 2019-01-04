#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_enough_input_info_for_record_selection : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_enough_input_info_for_record_selection() { }
		~CIFast_IFast_ifastdbrkr_err_not_enough_input_info_for_record_selection() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_ENOUGH_INPUT_INFO_FOR_RECORD_SELECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough input information for record selection.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not enough input information for record selection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nicht genügend Informationen zur Auswahl eines Eintrags eingegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo suficiente información para la selección de un registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information saisie est insuffisante à la sélection d'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onvoldoende invoergegevens voor recordselectie")); }

        // Actions
	};
}



