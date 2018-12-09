#Begin to define the user-define-decoration
def begin_profile(filename , sortby):
    def wrapper(func):
        def profile_func(*arga , **argb):
            import cProfile,pstats
            p = cProfile.Profile()
            p.enable()
            result = func(*agra , **argb)
            p.disable()
            k = pstats.Stats(p).sort_stats(sortby)
            k.dump_stats(filename)
            return result
        return profile_func
    return wrapper

#end define the user-define-decoration
