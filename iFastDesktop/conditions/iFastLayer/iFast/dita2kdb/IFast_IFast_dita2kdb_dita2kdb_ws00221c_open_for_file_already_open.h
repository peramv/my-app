#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_for_file_already_open : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_for_file_already_open() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_for_file_already_open() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_OPEN_FOR_FILE_ALREADY_OPEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Representative Code does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun conseiller financier exist avec les co-ordonnées que vous avez spécifié")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter-Code existiert nicht. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de representante de ventas no existe. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de représentant des ventes inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordigerscode bestaat niet. Vul opnieuw in")); }

        // Actions
	};
}



