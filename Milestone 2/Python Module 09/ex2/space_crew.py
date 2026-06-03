from pydantic import BaseModel, Field, ValidationError, model_validator
from datetime import datetime
from enum import Enum


class Rank(Enum):
    cadet = "cadet"
    officer = "officer"
    lieutenant = "lieutenant"
    captain = "captain"
    commander = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(..., min_length=3, max_length=10)
    name: str = Field(..., min_length=2, max_length=50)
    rank: Rank
    age: int = Field(..., ge=18, le=80)
    specialization: str = Field(..., min_length=3, max_length=30)
    years_experience: int = Field(..., ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    mission_id: str = Field(..., min_length=5, max_length=15)
    mission_name: str = Field(..., min_length=3, max_length=100)
    destination: str = Field(..., min_length=3, max_length=50)
    launch_date: datetime = Field(...)
    duration_days: int = Field(..., ge=1, le=3650)
    crew: list[CrewMember] = Field(..., min_length=1, max_length=12)
    mission_status: str = Field(default="planned")
    budget_millions: float = Field(..., ge=1.0, le=10000.0)

    @model_validator(mode='after')
    def validate_mission(self) -> 'SpaceMission':
        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with 'M'")

        has_commander_or_captain = any(
            member.rank in (Rank.commander, Rank.captain)
            for member in self.crew)
        if not has_commander_or_captain:
            raise ValueError("Mission must have at least "
                             "one Commander or Captain")

        if self.duration_days > 365:
            experienced_count = 0
            for member in self.crew:
                if member.years_experience >= 5:
                    experienced_count = experienced_count + 1

            total_crew = len(self.crew)
            experienced_percentage = experienced_count / total_crew

            if experienced_percentage < 0.5:
                raise ValueError("Long missions need 50% "
                                 "experienced crew (5+ years)")

        inactive = any(
            not member.is_active
            for member in self.crew)
        if inactive:
            raise ValueError("All crew members must be active")

        return self


def main() -> None:
    print("Space Mission Crew Validation")
    print("=========================================")

    print("Valid mission created:")
    try:
        mission = SpaceMission(
            mission_id="M2024_MARS",
            mission_name="Mars Colony Establishment",
            destination="Mars",
            launch_date=datetime.now(),
            duration_days=900,
            budget_millions=2500.0,
            crew=[
                CrewMember(
                    member_id="SC001",
                    name="Sarah Connor",
                    rank=Rank.commander,
                    age=35,
                    specialization="Mission Command",
                    years_experience=12
                ),
                CrewMember(
                    member_id="JS002",
                    name="John Smith",
                    rank=Rank.lieutenant,
                    age=28,
                    specialization="Navigation",
                    years_experience=6
                ),
                CrewMember(
                    member_id="AJ003",
                    name="Alice Johnson",
                    rank=Rank.officer,
                    age=25,
                    specialization="Engineering",
                    years_experience=4
                )
            ]
        )

        print(f"Mission: {mission.mission_name}")
        print(f"ID: {mission.mission_id}")
        print(f"Destination: {mission.destination}")
        print(f"Duration: {mission.duration_days} days")
        print(f"Budget: ${mission.budget_millions}M")
        print(f"Crew size: {len(mission.crew)}")
        print("Crew members:")
        for member in mission.crew:
            print(f"- {member.name} ({member.rank.value}) - "
                  f"{member.specialization}")

    except ValidationError as e:
        prefix = "Value error, "
        error_msg = e.errors()[0]['msg']
        if error_msg.startswith(prefix):
            error_msg = error_msg[len(prefix):]
        print(error_msg)

    print("\n=========================================")
    print("Expected validation error:")
    try:
        mission = SpaceMission(
            mission_id="M2024_MARS",
            mission_name="Mars Colony Establishment",
            destination="Mars",
            launch_date=datetime.now(),
            duration_days=900,
            budget_millions=2500.0,
            crew=[
                CrewMember(
                    member_id="SC001",
                    name="Sarah Connor",
                    rank=Rank.cadet,
                    age=35,
                    specialization="Mission Command",
                    years_experience=12
                ),
                CrewMember(
                    member_id="JS002",
                    name="John Smith",
                    rank=Rank.officer,
                    age=28,
                    specialization="Navigation",
                    years_experience=6
                ),
                CrewMember(
                    member_id="AJ003",
                    name="Alice Johnson",
                    rank=Rank.officer,
                    age=25,
                    specialization="Engineering",
                    years_experience=4
                )
            ]
        )

        print(f"Mission: {mission.mission_name}")
        print(f"ID: {mission.mission_id}")
        print(f"Destination: {mission.destination}")
        print(f"Duration: {mission.duration_days} days")
        print(f"Budget: ${mission.budget_millions}M")
        print(f"Crew size: {len(mission.crew)}")
        print("Crew members:")
        for member in mission.crew:
            print(f"- {member.name} ({member.rank.value}) - "
                  f"{member.specialization}")

    except ValidationError as e:
        prefix = "Value error, "
        error_msg = e.errors()[0]['msg']
        if error_msg.startswith(prefix):
            error_msg = error_msg[len(prefix):]
        print(error_msg)


if __name__ == "__main__":
    main()
