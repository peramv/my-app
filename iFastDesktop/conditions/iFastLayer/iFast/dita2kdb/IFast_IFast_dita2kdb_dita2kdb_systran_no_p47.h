#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_systran_no_p47 : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_systran_no_p47() { }
		~CIFast_IFast_dita2kdb_dita2kdb_systran_no_p47() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTRAN_NO_P47")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Business area has changed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Business area has changed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Geschäftsbereich hat sich geändert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El área de negocios ha cambiado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le secteur de marché a changé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrijfsgebied is gewijzigd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie einen neuen Arbeitstyp.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sélectionnez un nouveau type de travail.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Selecteer een nieuw werktype")); }
	};
}



