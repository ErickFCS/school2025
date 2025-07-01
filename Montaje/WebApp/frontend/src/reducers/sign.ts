import { newNotification } from "./notification";
import { In } from "../services/sign";
import { User } from "../types/user";
import { Dispatch, UnknownAction, createSlice } from "@reduxjs/toolkit";


const signSlice = createSlice({
    initialState: {
        user: null as User | null,
        loading: false
    },
    name: "sign",
    reducers: {
        clearSign() {
            return {
                user: null,
                loading: false
            };
        },
        setLoading(state, action) {
            return {
                user: state.user,
                loading: action.payload as boolean
            }
        },
        setSign(_state, action) {
            return {
                user: action.payload as User,
                loading: false
            };
        }
    }
});
export const { setSign, clearSign, setLoading } = signSlice.actions;

export const signIn = (user: User) => (
    async (dispatch: Dispatch) => {
        try {
            dispatch(setLoading(true));
            const token = await In(user);
            dispatch(setLoading(false));
            localStorage.setItem("token", token);
            dispatch(setSign(user));
            dispatch(newNotification({
                message: "Sign in successful",
                variant: "success"
            }));
        } catch (error) {
            console.error("Sign in failed:", error);
            dispatch(newNotification({
                message: "Sign in failed",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction;

export const signOut = () => (
    async (dispatch: Dispatch) => {
        localStorage.removeItem("token");
        dispatch(clearSign());
        dispatch(newNotification({
            message: "Sign out successful",
            variant: "success"
        }));
    }
) as unknown as UnknownAction;

const signReducer = signSlice.reducer;
export default signReducer;
