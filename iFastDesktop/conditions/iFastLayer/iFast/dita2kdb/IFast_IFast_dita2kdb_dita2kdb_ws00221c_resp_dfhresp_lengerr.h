#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_lengerr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_lengerr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_lengerr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_LENGERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% is mandatory unless posting an allocation trade. Indicate a fund or access the Allocations screen to create an allocation structure for this entry.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% est obligatoire a moins qu'il s'agisse de la comptabilisation d'une operation d'affectation. Indiquez un fonds ou accedez a l'ecran des Affectations pour creer une structure d'affectation pour cette entree.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% ist obligatorisch, wenn Sie kein Zuweisungsdatum verbuchen. Markieren Sie einen Fonds oder gehen Sie zum Zuweisungs-Bildschirm, um eine Zuweisungsstruktur für diesen Eintrag zu erstellen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% es obligatorio a menos que introduzca una operación de asignación. Indique un fondo o acceda a la pantalla de asignaciones para crear una estructura de asignación para esta entrada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% doit être rempli sauf si vous enregistrez une transaction de répartition. Indiquez un fonds ou accédez à l'écran de la répartition afin de créer une structure de répartition pour cette saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% is verplicht tenzij er een allocatietransactie wordt geboekt. Geef een fonds aan of ga naar het scherm Allocaties om een allocatiestructuur voor deze eenheid te maken")); }

        // Actions
	};
}



