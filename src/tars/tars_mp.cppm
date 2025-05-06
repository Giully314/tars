// tars/tars_mp.cppm
// PURPOSE: Define metaprogramming utilities.
//
// DESCRIPTION:
//

export module tars.mp;

namespace tars {

template<auto Id>
struct Counter {
    struct Generator {
        friend consteval auto is_defined(Counter) {
            return true;
        }
    };

    friend consteval auto is_defined(Counter);

    template<typename Tag = Counter, auto = is_defined(Tag{})>
    static consteval auto exists(auto) {
        return true;
    }

    static consteval auto exists(...) {
        return Generator(), false;
    }
};

export template<auto Id = int{}, auto = [] {}>
consteval auto unique_id() {
    if constexpr(!Counter<Id>::exists(Id)) {
        return Id;
    } else {
        return unique_id<Id + 1>();
    }
}

} // namespace tars
