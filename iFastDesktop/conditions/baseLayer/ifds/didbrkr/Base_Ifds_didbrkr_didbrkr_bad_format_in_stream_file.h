#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_bad_format_in_stream_file : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_bad_format_in_stream_file() { }
		~CBase_Ifds_didbrkr_didbrkr_bad_format_in_stream_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_BAD_FORMAT_IN_STREAM_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %TAG% a depasse la longueur maximale de %VALUE% caracteres.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Feld %TAG% hat die maximale Länge %VALUE% überschritten.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez la valeur appropriee.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie einen entsprechenden Wert ein.")); }
	};
}



