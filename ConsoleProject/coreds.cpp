#include "coreds.h"

void CoreDS::AddExercise(Exercise *ex)
{
    m_exercise_id_map.insert(ExerciseIDPair(ex->GetExerciseID(), ex));
    m_exercise_string_map.insert(ExerciseStringPair(ex->GetName(), ex));

}

Exercise* CoreDS::GetExercise(int ID)
{
    ExerciseIDMap::iterator m_it = m_exercise_id_map.find(ID);
    if (m_it == m_exercise_id_map.end()) {
        printf("returning null\n");
        return NULL;
    }
    else {
        return m_it->second; //second location in pair
    }
}

void CoreDS::PrintExercises()
{
    for (ExerciseStringMap::iterator m_it = m_exercise_string_map.begin();
         m_it != m_exercise_string_map.end();
         m_it++) {
        printf("%s\n", m_it->second->GetName().c_str());
    }
}
