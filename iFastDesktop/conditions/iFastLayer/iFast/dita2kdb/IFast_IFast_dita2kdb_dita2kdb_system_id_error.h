#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_system_id_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_system_id_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_system_id_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTEM_ID_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Account with key %KEY% was not in repository.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Account with key %KEY% was not in repository.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Konto mit Schlüssel %KEY% war nicht im Repository.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  La cuenta con clave %KEY% no estaba en el depósito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le compte de clé %KEY% n'est pas dans le référentiel.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Account met sleutel %KEY% bevond zich niet in verzamelbestand")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Objekt initialisiert wurde.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify that object is initialized.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'objet est initialisé.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het object is geïnitialiseerd")); }
	};
}



