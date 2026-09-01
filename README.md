# Hotel Reservation System

A console-based hotel reservation system in C++ with per-day CSV persistence and reporting.

Built for CSIS-297 (Intermediate C++) at Grossmont College. The system tracks four room types
across 122 rooms, attaches customer records to individual room numbers, logs every reservation and
cancellation to disk, and reloads the day's state on startup.

## Design

### Room type hierarchy

`Room` is a base class holding inventory state and the reservation map. Four types derive from it:

```cpp
class Standard  : public Room { ... };   // Courtyard, rooms 101-170
class Scenic    : public Room { ... };   // rooms 201-235
class Deluxe    : public Room { ... };   // rooms 301-315
class Penthouse : public Room { ... };   // rooms 401-402
```

`reserve()`, `reserveRandom()`, and `cancelReservation()` are virtual, and `Room` declares a virtual
destructor. Adding a room type means adding one class with its number range and price.

### Customer records

Reservations are stored as `map<int, Customer>`, keyed by room number, so a reserved room carries the
guest's name, phone, and email rather than just an occupied flag. Reports read straight off that map.

### Persistence

Two CSV files are written on every state change:

- `reservations_log_MM-DD-YYYY.csv` for the current day, written with a header row
- `master_log.csv` accumulating across days

Both record date, action, room type, room number, status, revenue, and the three customer fields.
On startup the program looks for today's log and rebuilds state from it, so reservations survive a
restart. If no log exists, it reports that and starts fresh.

## What it does

- Reserve a specific room by number, or take a random available one
- Cancel a reservation and return the room to inventory
- Inventory report: available and reserved counts per type, with room numbers and guest details
- Revenue report for the day
- Browse archived logs from previous days
- Date entry validated by regex **and** checked as a real calendar date
- Menu-driven interface with input validation at every prompt

## What it does not do

- **Single-night reservations only.** Everything is tied to "today"; there are no date ranges or
  multi-night stays.
- **No pricing logic beyond a flat per-type rate.** No seasonal rates, discounts, or taxes.
- **Flat-file storage, not a database.** CSV files with no transactions and no concurrency handling.
- **No authentication or roles.** Anyone at the terminal has full access.

## Building

Requires a C++17 compiler (`<filesystem>` and `<regex>`). No external dependencies.

```bash
git clone https://github.com/qedkymish/hotel-reservation-cpp.git
cd hotel-reservation-cpp
g++ -std=c++17 *.cpp -o hotel
./hotel
```

Builds clean with GCC 11 and 13 under `-Wall -Wextra`, and with MSVC. Valgrind and AddressSanitizer
report zero leaks and zero errors across a reserve, report, and cancel sequence.

## Sample output

```
=== Current Available Rooms ===
Room Type           Available Count
---------------------------------------------
Courtyard                        69
Scenic                           35
Deluxe Suite                     15
Penthouse                         2
---------------------------------------------

=== Current Reserved Rooms ===
Room Type            Reserved Count | Room Numbers
--------------------------------------------------------
Courtyard                         1 | Room 101: John Smith (6195551234, john@example.com)
Scenic                            0 | None
Deluxe Suite                      0 | None
Penthouse                         0 | None
--------------------------------------------------------
```

The corresponding log line:

```
Date,Action,RoomType,RoomNumber,Status,Revenue,CustomerName,CustomerPhone,CustomerEmail
09-01-2026,Reservation,Courtyard,101,Confirmed,125.000000,John Smith,6195551234,john@example.com
```

## Possible next steps

- Format revenue to two decimal places; it currently writes as a raw `double` (`125.000000`)
- Give `master_log.csv` the same header row the per-day log gets, so it opens cleanly in a spreadsheet
- Multi-night reservations with check-in and check-out dates
- Replace the flat CSV store with SQLite, which would also make cancellations transactional
- Extract the reporting code from `Hotel` into its own class; `Hotel.cpp` is doing too much
