import { createSlice, Dispatch, UnknownAction } from "@reduxjs/toolkit";
import { In } from "../services/sign";
import { User } from "../types/user";
import { newNotification } from "./notification";


const signSlice = createSlice({
    initialState: null as User | null,
    name: "sign",
    reducers: {
        setSign(_state, action) {
            return action.payload as User;
        },
        clearSign() {
            return null;
        }
    }
});
export const { setSign, clearSign } = signSlice.actions;

export const signIn = (user: User) => (
    async (dispatch: Dispatch) => {
        try {
            const token = await In(user);
            localStorage.setItem("token", token);
            dispatch(setSign(user));
            dispatch(newNotification({
                message: "Sign in successful",
                variant: "success"
            }))
        } catch (error) {
            console.error("Sign in failed:", error);
            dispatch(newNotification({
                message: "Sign in failed",
                variant: "danger"
            }));
        }
    }
) as unknown as UnknownAction

export const signOut = () => (
    async (dispatch: Dispatch) => {
        localStorage.removeItem("token");
        dispatch(clearSign());
        dispatch(newNotification({
            message: "Sign out successful",
            variant: "success"
        }));
    }
) as unknown as UnknownAction

const signReducer = signSlice.reducer
export default signReducer;