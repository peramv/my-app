#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_sts_error : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_sts_error() { }
		~CBase_Ifds_dita2kdb_dita2kdb_sts_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_STS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Tried to insert duplicate key %KEY% in FieldDetails map.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Tried to insert duplicate key %KEY% in FieldDetails map.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Eintrag ist leer oder enthält nur Leerzeichen. Bitte geben Sie ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Se intentó insertar una clave %KEY% repetida en el mapa FieldDetails.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Tentative d'insertion d'une clé de copie %KEY% dans l'application des détails du champ.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Er is geprobeerd om een dubbele sleutel %KEY% in te voegen in de folder FieldDetails.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



