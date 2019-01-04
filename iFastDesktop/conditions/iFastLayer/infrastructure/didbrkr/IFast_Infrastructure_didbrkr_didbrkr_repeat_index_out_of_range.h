#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_repeat_index_out_of_range : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_repeat_index_out_of_range() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_repeat_index_out_of_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REPEAT_INDEX_OUT_OF_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Repeat number %num% requested from Data object %props%.  Actual number of repeats is %numrpts%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Repeat number %num% requested from Data object %props%.  Actual number of repeats is %numrpts%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wiederholungsnummer %num% angefragt von Datenobjekt %props%.  Tatsächliche Nummer von Wiederholungen ist %numrpts%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se solicitó el número de repetición %num% del objeto de datos %props%.  El número real de repeticiones es %numrpts%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nombre de répétition %num% demandé par l'objet de données %props%. Le nombre actuel de répétitions est %numrpts%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Herhalingsaantal %num% aangevraagd van gegevensobject %props%.  Werkelijk aantal herhalingen is %numrpts%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



